package BT2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class ChatClient {
	public static void main(String[] args) throws Exception
	{
		Socket socket = new Socket("localhost", 7000);
		DataInputStream din = new DataInputStream(socket.getInputStream());
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		//Nhap chuoi de gui den Server
		Scanner kb = new Scanner(System.in);
		while(true)
		{
			System.out.println("Client: ");
			String msg = kb.nextLine();
			dos.writeUTF("Client: " + msg);
			dos.flush();
			//Client nhan dl tu Server gui lai
			String st = din.readUTF();
			System.out.println(st);
			kb = kb.reset();
		}
	}
}
