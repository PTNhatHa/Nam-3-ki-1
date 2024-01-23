package UDPChat;

import java.io.IOException;
import java.net.*;
import java.util.*;

public class UDPChatServer {

	public static void main(String[] args) throws IOException {
		DatagramSocket serverSocket = new DatagramSocket(7000);
		System.out.println("Server is started");
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];
		Scanner s = new Scanner(System.in);
		while(true)
		{
			// Nhận dl
			DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
			serverSocket.receive(receivePacket);
			InetAddress IPAddress = receivePacket.getAddress();
			int port = receivePacket.getPort();
			String receiveMsg = new String(receivePacket.getData(), 0, receivePacket.getLength());
			System.out.println(receiveMsg);
			// Gửi dl
			System.out.print("Server: ");
			String sendMsg = s.nextLine();
			sendData = ("Server: " + sendMsg).getBytes();
			DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
			serverSocket.send(sendPacket);
			s = s.reset();
		}
	}

}
