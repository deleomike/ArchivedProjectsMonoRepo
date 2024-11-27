import java.net.*;

public final class webserver {
	
	//Main function
	public static void main(String argv[]) throws Exception
	{
		//Set the port number
		int port = 6789; //web port
		//normally, web servers process service requests that they receive
		//through well known port number 80. you can choose any port higher
		//than 1024, but remember to use the same port when making requests
		//to your web server
		
		//Establish the listen socket with SERVERSOCKET to the port 6789
		ServerSocket sock = new ServerSocket(port);
		
		//Provide a message for users.
		System.out.println("The server is listening.");
		
		//Process HTTP service requests in an infinite loop.
		while (true) {
			//Listen for a TCP connection request
			Socket s = sock.accept(); //blocks until a request is received
			
			//Connection Requested
			// Construct an object to process the Http request message
			HttpRequest request = new HttpRequest(s);

			// Create a new thread to process the request
			Thread thread = new Thread(request);

			// Start the thread
			thread.start();
				
		}
	}

}

