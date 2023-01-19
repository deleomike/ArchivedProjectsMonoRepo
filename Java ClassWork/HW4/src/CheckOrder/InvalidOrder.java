package CheckOrder;

public class InvalidOrder extends Exception {
    public String Name;
    public int QuantityAvail;
    public int QuantityReq;

    public InvalidOrder(){
        Name = "";
        QuantityAvail = 0;
        QuantityReq = 0;
    }

    public InvalidOrder(String Name, int QuantityAvail, int QuantityReq){
        this.Name = Name;
        this.QuantityAvail = QuantityAvail;
        this.QuantityReq = QuantityReq;
    }
}
