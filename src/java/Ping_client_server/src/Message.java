
/**
 * Message.java
 *
 * For use by CMPEN 461 Fall 2018 Penn State only
 */

import java.net.InetAddress;

public class Message {

    private InetAddress addr;
    private int port = 0;
    private String message = null;

    /** constructor **/
    public Message(InetAddress addr, int port, String message) {
        this.addr = addr;
        this.port = port;
        this.message = message;
    }

    /** Get the IP address **/
    public InetAddress getIP() {
        return addr;
    }

    /** Get the contents of the message **/
    public String getContents() {
        return message;
    }

    /** Get the port number **/
    public int getPort() {
        return port;
    }

}
