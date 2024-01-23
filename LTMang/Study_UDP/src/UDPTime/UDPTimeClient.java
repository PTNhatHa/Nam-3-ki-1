package UDPTime;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UDPTimeClient {

	public static void main(String[] args) throws IOException {
		DatagramSocket clientSocket = new DatagramSocket();
		InetAddress IPAddress = InetAddress.getByName("localhost");
		byte[] receiveData = new byte[1024];
		byte[] sendData = new byte[1024];
		sendData = "getDate".getBytes();
		// Tạo datagram có nd yêu cầu loại dl dể gửi cho Server
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
		// Gửi dl cho Server
		clientSocket.send(sendPacket);
		// Tạo datagram rỗng để nhận dl từ Client
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		// Nhận dl từ Client
		clientSocket.receive(receivePacket);
		// Lấy dl từ packet nhận đc
		String str = new String(receivePacket.getData());
		System.out.println(str);
		clientSocket.close();
	}
}
