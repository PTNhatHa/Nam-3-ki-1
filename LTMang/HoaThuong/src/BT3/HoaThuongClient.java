package BT3;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class HoaThuongClient {

	public static void main(String[] args) throws Exception 
	{
		Socket socket = new Socket("localhost", 7000);
		System.out.println("Client is started \n");
		DataInputStream din = new DataInputStream(socket.getInputStream());
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		//Nhap chuoi de gui den Server
		Scanner kb = new Scanner(System.in);
		while(true)
		{
			System.out.println("Nhập chuỗi bất kỳ: ");
			String msg = kb.nextLine();
			dos.writeUTF(msg);
			dos.flush();
			//Client nhan dl tu Server gui lai
			String st = din.readUTF();
			System.out.println(st);
			kb = kb.reset();
		}
	}

}
