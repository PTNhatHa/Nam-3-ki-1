package UDPxulychuoi;

import java.io.*;
import java.net.*;
import java.util.*;

public class UDPxulychuoiClient {

	public static void main(String[] args) throws IOException {
		DatagramSocket clientSocket = new DatagramSocket();
		int port = 7000;
		InetAddress IPAddress = InetAddress.getByName("localhost");
		System.out.println("Client is started");
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];
		
		Scanner s = new Scanner(System.in);
		System.out.println("Nhập chuỗi: ");
		String msg = s.nextLine();
		sendData = msg.getBytes();
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
		clientSocket.send(sendPacket);
		
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		clientSocket.receive(receivePacket);
		String str = new String(receivePacket.getData());
		System.out.println("Kq:\n" + str);
		clientSocket.close();
	}

}
