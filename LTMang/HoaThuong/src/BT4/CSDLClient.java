package BT4;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class CSDLClient {

	public static void main(String[] args) throws UnknownHostException, IOException {
		Socket socket = new Socket("localhost", 7002);
		DataInputStream din = new DataInputStream(socket.getInputStream());
		System.out.println("Client:");
		String msg = din.readUTF();
		System.out.println(msg);
		socket.close();
	}

}
