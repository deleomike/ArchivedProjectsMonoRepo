import java.net.Socket;
import java.util.StringTokenizer;
import java.io.*;

final class HttpRequest implements Runnable
{
	//Runnable allows this class to be threaded
	
	final static String CRLF = "\r\n";
	Socket socket;
	
	public HttpRequest(Socket socket) throws Exception
	{
		this.socket = socket;
	}
	
	public void run()
	{
		try {
			processRequest();
		} catch(Exception e) {
			System.out.println(e);
		}
	}
	
	private void processRequest() throws Exception
	{
		//Get a reference to the socket's input and output streams
		InputStream is = socket.getInputStream();
		DataOutputStream os =  new DataOutputStream(socket.getOutputStream());
		
		
		//Set up input stream filters
		BufferedReader br = new BufferedReader(new InputStreamReader(is));
		
		//Get the requested line of the HTTP request message
		String requestLine = br.readLine();	//Gets first line, first line is request line
		
		//Display the request line.
		System.out.println();
		System.out.println(requestLine);
		
		//Extract the filename from the request line
		StringTokenizer tokens =  new StringTokenizer(requestLine);
		tokens.nextToken();	//skip over method, which should be get
		String filename = tokens.nextToken();
		
		//Prepend a "." so that the file request is within the current directory
		filename = "." + filename;
		
		//Open the requested file
		//prevents the thread from termination if there is an error
		FileInputStream fis = null;
		boolean file_exists = true;
		try {
			fis = new FileInputStream(filename);
			System.out.println("does exist");
		} catch(FileNotFoundException e) {
			file_exists = false;
			System.out.println("does not exist");
		}
		
		//Construct the response message
		String status_line = null;
		String content_type_line = null;
		String entity_body = null;
		if (file_exists) {
			status_line = "HTTP/1.1 200 OK" + CRLF;
			content_type_line="Content-type: " + contentType(filename) + CRLF;
			
		}
		else {
			status_line = "HTTP/1.1 404 Not Found" + CRLF;
			content_type_line = "text/html" + CRLF;
			entity_body = "<HTML>" + "<HEAD><TITLE>NOT FOUND</TITLE></HEAD>"
						+ "<BODY>404 File Not Found</BODY></HTML>";
		}
		
		//Send the status line
		os.writeBytes(status_line);
		
		//Send the content type line
		os.writeBytes(content_type_line);

		
		//Send a blank line to indicate the end of the header lines
		os.writeBytes(CRLF);
		
		//Send the entity body
		if (file_exists) {
			sendBytes(fis,os);
			fis.close();
		}
		else {
			os.writeBytes(entity_body);
		}
		
		//Get and display header lines
		String headerLine = null;
		//we don't know how many lines to get, so do a while loop till the end
		while((headerLine = br.readLine()).length() != 0) {
			System.out.println(headerLine);
		}
		
		//Close streams and socket
		socket.close();
		fis.close();
		br.close();
		is.close();
		os.close();
	}
	
	private static void sendBytes(FileInputStream fis, OutputStream os) throws Exception
	{
		//construct a 1K buffer to hold bytes on their way to the socket
		byte[] buffer = new byte[1024];
		int bytes = 0;
		
		//copy requested file into the socket's output stream
		while((bytes = fis.read(buffer)) != -1) {
			os.write(buffer,0,bytes);
		}
	}
	private static String contentType(String fileName) {
		if (fileName.endsWith(".htm") || fileName.endsWith(".html")) {
			return "text/html";
		}
		if (fileName.endsWith(".gif") || fileName.endsWith(".GIF")) {
			return "image/gif";
		}
		if (fileName.endsWith(".jpeg")) {
			return "image/jpeg";
		}
		if (fileName.endsWith(".jpg")) {
			return "image/jpeg";
		}
		
		return "application/octet-stream";
	}
}
