

class PlaceManager:

    place = ""

    def __init__(self, place, startDate, endDate):

        self.place = place

        self.startDate = startDate

        self.endDate = endDate

        self.Locations = []


    def addLocation(self, Location):

        self.Locations.append(Location)

