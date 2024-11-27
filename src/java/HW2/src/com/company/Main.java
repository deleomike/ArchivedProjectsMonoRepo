package com.company;

import java.util.*;

public class Main {

    static Map<String, String> dict = new HashMap<String,String>() {{
        put("A",".-");
        put("B","-...");
        put("C","-.-.");
        put("D","-..");
        put("E",".");
        put("F","..-.");
        put("G","--.");
        put("H","....");
        put("I","..");
        put("J",".---");
        put("K","-.-");
        put("L",".-..");
        put("M","--");
        put("N","-.");
        put("O","---");
        put("P",".--.");
        put("Q","--.-");
        put("R",".-.");
        put("S","...");
        put("T","-");
        put("U","..-");
        put("V","...-");
        put("W",".--");
        put("X","-..-");
        put("Y","-.--");
        put("Z","--..");

        put("1",".----");
        put("2","..---");
        put("3","...--");
        put("4","....-");
        put("5",".....");
        put("6","-....");
        put("7","--...");
        put("8","---..");
        put("9","----.");
        put("0","-----");


        put(" ","       ");

    }};

    public static void main(String[] args) {
	// write your code here
        int x  = 0;
        int y = 3;
        int z  = 5;
        x = y = z;

        System.out.println("Type in phrases to convert into morse code. type ##QUIT## on a new line to stop");
        Scanner scan = new Scanner(System.in);
        while(true){

            String s = scan.nextLine();
            if (s.equals("##QUIT##")){
                break;
            }
            System.out.println(EnglishToMorse(s));
        }

        reservations United = new reservations();
        zone NA = zone.NORTH_AMERICA;
        zone A = zone.AFRICA;
        zone AS = zone.ASIA;
        zone POLY = zone.POLYNESIA;
        plane_type BUS = plane_type.BUSINESS;
        plane_type PRIV = plane_type.PRIVATE;
        plane_type ECO = plane_type.ECONOMY;

        trip A1 = new trip();
        trip A2 = new trip(221,zone.POLYNESIA,zone.NORTH_AMERICA,plane_type.PRIVATE);
        United.addTrip(A1);
        United.addTrip(A2);


        while(true){
            int choice = 0;
            System.out.print("1. Order Ticket For Specific Trip\n2. Cancel Tickets For Specific Trip\n3. Add Trip to Reservations List\nType -1 to exit\n");
            choice = scan.nextInt();

            if (choice == 1){
                System.out.print("===========================\nOrder Tickets\nInput Trip Number: ");
                int trip_id = scan.nextInt();
                System.out.print("Requested Number of Seats: ");
                int requested_seats = scan.nextInt();
                if (United.containsTrip(trip_id)){
                    if (requested_seats > United.seatsLeft(trip_id)){
                        System.out.printf("Seats Requested: %d\nSeats Available: %d\nNot enough seats. Returning to Menu\n",requested_seats,United.seatsLeft(trip_id));
                    }
                    else{
                        System.out.printf("Estimated cost for %d ticket(s): $%d\nConfirm? y/n",requested_seats,United.getPrice(trip_id,requested_seats));
                        scan.nextLine();
                        String answer = scan.nextLine();
                        if (answer.equals("y") || answer.equals("Y")){
                            for (int i = 0; i < requested_seats; i++){
                                System.out.printf("Type Name of Traveler %d/%d: ",i+1,requested_seats);
                                if (i > 0){ scan.nextLine();}
                                String name = scan.nextLine();
                                System.out.printf("Type Passport ID of Traveler %d/%d: ",i+1,requested_seats);
                                int id = scan.nextInt();
                                traveler t = new traveler(name,id);
                                United.addTravelerTrip(t,trip_id);
                            }
                        }
                    }
                }
                System.out.println("===========================");

            } else if (choice == 2) {
                System.out.print("===========================\nCancel Trip Ticket\nInput Trip Number: ");
                int trip_id = scan.nextInt();
                System.out.print("Input Passport ID: ");
                int id = scan.nextInt();
                if (United.containsTrip(trip_id)){
                    for (int i = 0; i < United.roster.size(); i++){
                        if (United.roster.get(i).ID == trip_id){
                            United.roster.get(i).remove_traveler(id);
                            break;
                        }
                    }
                }
                else{
                    System.out.println("Trip Not Found");
                }
                System.out.println("===========================");

            } else if (choice == 3){
                System.out.print("===========================\nAdd Trip\nInput Trip Number: ");
                int id = scan.nextInt();
                System.out.print("Available Zones\n------------------\nNorth America: 0\nAfrica: 1\nAsia: 2\nPolynesia: 3\n------------------\n");
                System.out.print("Select Destination: ");
                int dest  = scan.nextInt();
                System.out.print("Select Zone You Are flying out of: ");
                int source = scan.nextInt();
                System.out.print("Plane Types\n------------------\nPrivate: 0\nBusiness: 1\nEconomy: 2\n------------------\n");
                System.out.print("Select Plane Type: ");
                int plane_num = scan.nextInt();

                zone destination = selectZone(dest);
                zone src = selectZone(source);

                plane_type plane = selectPlane(plane_num);

                trip t = new trip(id,destination,src,plane);

                United.roster.add(t);

                System.out.println("Trip Successfully added");

                System.out.println("===========================");
            }
        }


    }

    static String EnglishToMorse(String ss){
        StringBuilder sb = new StringBuilder();

        String s = ss.toUpperCase();


        for (int i = 0; i < s.length(); i++){
            if (sb.toString().length() != 0 && (!s.substring(i-1,i).equals(" ") && !s.substring(i,i+1).equals(" "))){
                sb.append(" ");
            }
            if (dict.containsKey(s.substring(i,i+1))){
                sb.append(dict.get(s.substring(i,i+1)));
            }
        }

        return sb.toString();
    }

    static private zone selectZone(int num){
        zone destination;
        if (num == 0){ destination = zone.NORTH_AMERICA;}
        else if (num == 1){ destination = zone.AFRICA;}
        else if (num == 2) {destination = zone.ASIA;}
        else { destination = zone.POLYNESIA;}
        return destination;
    }

    static private plane_type selectPlane(int num){
        plane_type plane;
        if (num == 0){ plane = plane_type.PRIVATE;}
        else if(num == 1){ plane = plane_type.BUSINESS;}
        else { plane = plane_type.ECONOMY; }
        return plane;
    }
}


enum plane_type{

    PRIVATE(10),
    BUSINESS(20),
    ECONOMY(100);

    int seats;

    plane_type(int seats){ this.seats = seats; }
}

enum zone{
    NORTH_AMERICA(500),
    AFRICA(1000),
    ASIA(2000),
    POLYNESIA(3000);

    int cost;

    zone(int cost) { this.cost = cost; }
}

class reservations{
    ArrayList<trip> roster;

    reservations(){
        roster = new ArrayList<trip>();
    }

    void remove_traveler(int passport_id, int trip_ID){
        for (int i = 0; i < roster.size(); i++){
            if (roster.get(i).ID == trip_ID){
                roster.get(i).remove_traveler(passport_id);
                return;
            }
        }
        System.out.printf("Trip %d was not found in the system",trip_ID);
    }

    void addTrip(trip t){
        roster.add(t);
    }

    void addTravelerTrip(traveler t, int id){
        for (int i = 0; i < roster.size();i++){
            if (roster.get(i).ID == id){
                roster.get(i).add_traveler(t);
                return;
            }
        }
        return;
    }

    boolean containsTrip(int trip_id){
        for (int i = 0;i < roster.size(); i++){
            if (roster.get(i).ID == trip_id){
                return true;
            }
        }
        return false;
    }

    int seatsLeft(int tripID){
        for (int i = 0; i < roster.size(); i++){
            if (roster.get(i).ID == tripID){
                return roster.get(i).type.seats - roster.get(i).manifest.size();
            }
        }
        return 0;
    }

    int getPrice(int trip_id, int seats){
        for (int i = 0; i < roster.size(); i++){
            if (roster.get(i).ID == trip_id){
                return roster.get(i).destination.cost * seats;
            }
        }
        return 0;
    }
    void order_tickets(int tickets){

    }

}

class trip{
    static int pilots = 2;
    static int plane_model = 747;

    int ID;

    ArrayList<traveler> manifest;

    plane_type type;

    zone destination;
    zone source;

    trip(){
        ID = 0;
        manifest = new ArrayList<traveler>();
        type = plane_type.PRIVATE;
        destination = zone.NORTH_AMERICA;
        source = zone.NORTH_AMERICA;
    }

    trip(int ID, zone destination, zone source, plane_type type){
        manifest = new ArrayList<traveler>();
        this.ID = ID;
        this.destination = destination;
        this.source = source;
        this.type = type;
    }

    void add_traveler(traveler m){
        if (manifest.size() == type.seats){
            System.out.printf("No Seats left for %s on flight %d\n",m.name,ID);
        }
        else{
            System.out.printf("Enjoy your flight %s on flight %d\n",m.name,ID);
            manifest.add(m);
        }
    }

    void remove_traveler(int ID){
        for (int i = 0; i < manifest.size(); i++){
            if (manifest.get(i).passport_id == ID){
                manifest.remove(i);
                System.out.printf("Trip %d has been cancelled for passenger %d\n",this.ID,ID);
                return;
            }
        }
        System.out.printf("Passenger with ID %d not found on flight %d reservation\n",ID,this.ID);
    }
}

class traveler{
    String name;
    int passport_id;

    traveler(){
        name = "John Doe";
        passport_id = 0;
    }

    traveler(String name, int id){ this.name = name; this.passport_id = id;}
}