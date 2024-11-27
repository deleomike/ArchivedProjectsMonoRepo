package CheckOrder;

public class ProductNotFound extends RuntimeException {
    public String Name;

    public ProductNotFound(){
        Name = "";
    }

    public ProductNotFound(String Name){
        this.Name = Name;
    }
}
