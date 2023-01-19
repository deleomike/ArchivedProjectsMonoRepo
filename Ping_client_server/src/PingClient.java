
/**
 * PingClient.java
 *
 * For use by CMPEN 461 Fall 2018 Penn State only
 */

import java.net.*;
import java.io.*;


public class PingClient {
    /**Socket which we use**/
    DatagramSocket socket;
    	
    /**Maximum length of a ping message**/
    static final int MAX_PING_LEN = 512;
    
    /** Create a datagram socket with a random port for sending UDP messages**/
    public void createSocket() {
    	try {
    		socket = new DatagramSocket(0);	//random open port
    	} catch(SocketException e) {
    		System.out.println("Error creating socket:" + e);
    	}
    }
    
    /** Create a datagram socket with specific port for receiving UDP messages**/
    public void createSocket(int port) {
    	try {
    		socket = new DatagramSocket(port);
    	} catch (SocketException e) {
    		System.out.println("Error creating socket: " + e);
    	}
    }
    
    /* Send a UDP ping message which is given as the argument */
    public void sendPing(Message ping) {
    	
    	InetAddress host = ping.getIP();
    	int port = ping.getPort();
    	String message = ping.getContents();
    	
    	try {
    		/*create a datagram packet addressed to the recipient */
    		DatagramPacket packet = new DatagramPacket(message.getBytes(),message.length(),host,port);
    		
    		/*Send the packet*/
    		socket.send(packet);
    		System.out.println("Sent message to " + host + ":" + port);
    	} catch(IOException e) {
    		System.out.println("Error sending packet: " + e);
    	}
    }
    
    /** Receive a UDP ping message and return the received message.
     * We throw an exception to indicate that the socket timed out
     * This can happen when a message is lost in the network.
     * @return Message
     * @throws SocketTimeoutException
     */
    public Message receivePing() throws SocketTimeoutException{
    	
    	/* Create packet for receiving the reply */
    	byte recvBuf[] = new byte[MAX_PING_LEN];
    	DatagramPacket recvPacket = new DatagramPacket(recvBuf,MAX_PING_LEN);
    	Message reply = null;
    	
    	/* Read message from socket */
    	try {
    		socket.receive(recvPacket);
    		
    		System.out.println("Received message from " +
    							recvPacket.getAddress() +
    							":" + recvPacket.getPort());
    		
    		String recvMsg = new String(recvPacket.getData());
    		System.out.println(recvMsg.trim());
    		reply = new Message(recvPacket.getAddress(),recvPacket.getPort(),recvMsg);
    	} catch(SocketTimeoutException e) {
    		throw e;
    	} catch(IOException e) {
    		System.out.println("Error reading from socket: " + e);
    	}
    	return reply;
    }

}