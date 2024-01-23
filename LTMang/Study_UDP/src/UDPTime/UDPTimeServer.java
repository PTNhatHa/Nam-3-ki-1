package UDPTime;

import java.io.IOException;
import java.net.*;
import java.net.SocketException;
import java.util.Date;

public class UDPTimeServer {

	public static void main(String[] args) throws IOException {
		// Gán cổng cho ct
		DatagramSocket serverSocket = new DatagramSocket(9876);
		// Tạo các mảng byte để chứa dl gửi và nhận
		System.out.println("Server is started");
		byte[] receiveData = new byte[1024];
		byte[] sendData = new byte[1024];
		while(true)
		{
			// Tạo gói rỗng để nhận dl từ Client
			DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
			// Nhận dl từ Client
			serverSocket.receive(receivePacket);
			// Lấy địa chỉ IP của Client
			InetAddress IPAddress = receivePacket.getAddress();
			// Lấy port của ct Client
			int port = receivePacket.getPort();
			// Lấy ngày giờ để gửi ngược lại Client
			String request = new String(receivePacket.getData());
			System.out.println(request);
			if(request.trim().equals("getDate"))
			{
				sendData = new Date().toString().getBytes();
			}
			else
			{
				sendData = "Server not know what you want".getBytes();
			}
			DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
			// Gửi dl lại cho Client
			serverSocket.send(sendPacket);
		}
	}

}
