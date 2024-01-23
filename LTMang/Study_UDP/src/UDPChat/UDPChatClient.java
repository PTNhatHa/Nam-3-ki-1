package UDPChat;

import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class UDPChatClient {

	public static void main(String[] args) throws IOException {
		DatagramSocket clientSocket = new DatagramSocket();
		int port = 7000;
		InetAddress IPAddress = InetAddress.getByName("localhost");
		System.out.println("Client is started");
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];
		Scanner s = new Scanner(System.in);
		while(true)
		{
			// Gửi dl
			System.out.print("Client: ");
			String sendMsg = s.nextLine();
			sendData = ("Client: " + sendMsg).getBytes();
			DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
			clientSocket.send(sendPacket);
			s = s.reset();
			// Nhận dl
			DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
			clientSocket.receive(receivePacket);
			String receiveMsg = new String(receivePacket.getData(), 0, receivePacket.getLength());
			System.out.println(receiveMsg);
		}
	}

}
