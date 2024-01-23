package UDP_CSDL;

import java.net.*;

public class UDP_CSDL_Client {

	public static void main(String[] args) throws Exception {
		DatagramSocket clientSocket = new DatagramSocket();
		int port = 7000;
		InetAddress IPAddress = InetAddress.getByName("localhost");
		byte[] receiveData = new byte[1024];
		byte[] sendData = new byte[1024];
		sendData = "ConnectDB".getBytes();
		// Gửi dl
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
		clientSocket.send(sendPacket);
		// Nhận dl
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		clientSocket.receive(receivePacket);
		String receive = new String(receivePacket.getData(), 0, receivePacket.getLength());
		System.out.println(receive);
	}

}
