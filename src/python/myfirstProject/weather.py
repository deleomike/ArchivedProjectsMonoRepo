import requests
import random

API_KEY = ""
BASE_URL = "http://dataservice.accuweather.com/"


def get_weather(location):
    location_url = BASE_URL + "locations/v1/search?q=" + \
        location.replace(' ', '%20') + "&apikey=" + API_KEY
    print("Querying Accuweather at " + location_url)
    req = requests.get(url=location_url)
    data = req.json()

    temp = "done"

    weather_url = BASE_URL + "forecasts/v1/hourly/1hour/" + \
        data[0]["Key"] + "?apikey=" + API_KEY

    req = requests.get(url=weather_url)
    data = req.json()

    temp = str(data[0]["Temperature"]["Value"]) + \
        data[0]["Temperature"]["Unit"]
    res = {"WeatherIcon": data[0]["WeatherIcon"],
           "Temp": temp,
           "IsDaylight": data[0]["IsDaylight"]}

    return res



def black_magic(res,emo):
    weather = res["WeatherIcon"]
    temp = res["Temp"]
    IsDaylight = res["IsDaylight"]

    Unit = temp[-1:]
    temp = float(temp[0:len(temp)-1])  # temperature without unit

    # print(weather)
    # print(temp)

    temp_mood = 0
    # do the linear regression for the temperature
    if Unit == "F":
        if temp == 68:
            temp_mood = 1
        elif temp < 32 or temp > 100:
            temp_mood = -1
        elif temp > 32 and temp < 68:  # lower section
            temp_mood = (temp - 50)/18
        elif temp > 68 and temp < 100:  # upper section
            temp_mood = (temp-86)/(-18)
        else:
            print("error")

    else:
        if temp == 20:
            temp_mood = 1
        elif temp < 32 or temp > 100:
            temp_mood = -1
        elif temp > 32 and temp < 68:  # lower section
            temp_mood = (temp - 10)/10
        elif temp > 68 and temp < 100:  # upper section
            temp_mood = (temp-30)/(-10)
        else:
            print("error")

    # day light weighting
    day_light_mood = 0
    if IsDaylight:
        day_light_mood = 1
    else:
        day_light_mood = -1

    # TODO: emo weight
    weights = {0.5, 0.4, 0.3, 0.2, 0.1, 0, -0.1, -0.2, -.3, -.4, -.5}
    weather_mood = 0
    # weather weighting
    if (weather >= 1 and weather <= 6):
        weather_mood = 1
    elif (weather >= 7 and weather <= 11):
        weather_mood = -0.1
    elif (weather >= 24 and weather <= 31):
        weather_mood = -0.5
    elif (weather >= 32 and weather <= 44):
        weather_mood = -1
    else:
        weather_mood = random.uniform(-0.8, 0.2)

    total = 0
    if emo == 1:
        total = 0.33*(temp_mood + day_light_mood + weather_mood)
    else:
        total = 0.25*(temp_mood + day_light_mood + weather_mood)

    # return two options. one with emotion and one without
    return total


def get_city(latitude, longitude):
    # get the city using longitude and latitude here

    loc_url = BASE_URL + "locations/v1/cities/geoposition/search?apikey=" + API_KEY + "&q="
    loc_url = loc_url + str(latitude) + "%2C" + str(longitude)

    print(loc_url)

    req = requests.get(url=loc_url)

    data = req.json()
    print(data)

    if data is None or not hasattr(data, "LocalizedName"):
        return "State College"
    else:
        return data["LocalizedName"]
