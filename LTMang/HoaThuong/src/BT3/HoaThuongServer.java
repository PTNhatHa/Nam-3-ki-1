package BT3;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HoaThuongServer {

	public static String chuthuong(String s)
	{
		String ch = "";
		char[] c = s.toCharArray();
        for(int i = 0; i < c.length; i++) 
        {
            if(c[i] >= 65 && c[i] <= 90)
            {
                c[i] += 32;
            }
        }
        ch = String.valueOf(c);
		return ch;
	}
	public static String chuhoa(String s)
	{
		String ch = "";
		char[] c = s.toCharArray();
        for(int i = 0; i < c.length; i++) 
        {
            if(c[i] >= 97 && c[i] <= 122)
            {
                c[i] -= 32;
            }
        }
        ch = String.valueOf(c);
		return ch;
	}
	public static String hoathuong(String s)
	{
		String ch = "";
		char[] c = s.toCharArray();
        for(int i = 0; i < c.length; i++)
        {
            if(c[i] >= 97 && c[i] <= 122)
            {
                c[i] -= 32;
            }
            else
            {
            	if(c[i] >= 65 && c[i] <= 90)
            	{
                    c[i] += 32;
            	}
            }
        }
        ch = String.valueOf(c);
		return ch;
	}

	public static void main(String[] args) throws Exception
	{
		ServerSocket server = new ServerSocket(7001);
		System.out.println("Server is started");
		Socket socket = server.accept();
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		DataInputStream din = new DataInputStream(socket.getInputStream());
		while(true)
		{
			//Nhan dl tu Client
			String st = din.readUTF();
			String msg = chuthuong(st) + "\n" + chuhoa(st) + "\n" + hoathuong(st) + "\n";
			dos.writeUTF(msg);
			dos.flush();
		}
	}

}
