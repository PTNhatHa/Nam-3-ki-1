package BT3;

import java.io.*;
import java.net.*;
import java.util.*;

public class Server_BT3 {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		ServerSocket socketServer = new ServerSocket(7000);
		System.out.println("Server is started");
		int count = 1;
		while(true)
		{
			Socket socket = socketServer.accept();
			new ClientHandlder(socket, count).start();
			count++;
		}
	}
}
class ClientHandlder extends Thread {
	static Set<DataOutputStream> writers = new HashSet<>();
	Socket socketServer;
	DataInputStream din;
	DataOutputStream dos;
	int count;
	
	public ClientHandlder(Socket socket, int c) throws IOException{
		this.socketServer = socket;
		din = new DataInputStream(socketServer.getInputStream());
		dos = new DataOutputStream(socketServer.getOutputStream());
		writers.add(dos);
		count = c;
	}
	public void run()
	{
		try {
			while(true)
			{
				String st = din.readUTF();
				for(DataOutputStream writer : writers)
				{
					writer.writeUTF("Client " + count + ": " + st + "\n");
					writer.flush();
				}
			}
		} catch (IOException e) {
			//e.printStackTrace();
		}
	}
}
