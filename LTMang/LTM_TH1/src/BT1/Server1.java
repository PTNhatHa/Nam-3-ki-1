package BT1;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server1 {
	public static void main(String[] args) throws Exception
	{
		ServerSocket socketServer = new ServerSocket(7000);
		System.out.println("Server is started");
		while(true)
		{
			Socket socket = socketServer.accept();
			int count = 0;
			new ClientHandlder(socket, count).start();;
			count++;
		}
	}
}

class ClientHandlder extends Thread {
	Socket socketServer;
	DataInputStream din;
	DataOutputStream dos;
	int count;
	
	public ClientHandlder(Socket socket, int c) throws IOException{
		this.socketServer = socket;
		din = new DataInputStream(socketServer.getInputStream());
		dos = new DataOutputStream(socketServer.getOutputStream());
		count = c;
	}
	public void run()
	{
		try {
			while(true)
			{
			String st = din.readUTF();
			String msg = chuoinguoc(st) + "\n" 
					+ chuthuong(st) + "\n" + chuhoa(st) + "\n" + hoathuong(st) + "\n"
					+ demtu(st) + "\n";
			dos.writeUTF(msg);
			dos.flush();
			}
		} catch (IOException e) {
			//e.printStackTrace();
		}
	}
	public static String chuoinguoc(String s)
	{
		String ch = "";
		char[] c = s.toCharArray();
        for(int i = c.length - 1; i >= 0; i--) 
        {
            ch += c[i];
        }
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
	public static String demtu(String s)
	{
		String ch = "";
		char[] c = s.toCharArray();
		int sotu=0, stt=0;
		// u e o a i
		int d1=0, d2=0, d3=0, d4=0, d5=0;
		while(String.valueOf(c[stt]) == " ")
		{
			stt++;
		}
        for(int i = stt; i < c.length; i++) 
        {
        	if(String.valueOf(c[i]).equalsIgnoreCase("u")) d1++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("e")) d2++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("o")) d3++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("a")) d4++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("i")) d5++;
        	if(i == c.length - 1 && String.valueOf(c[i]) != " ") 
        	{
        		sotu++;
        		break;
        	}
            if(String.valueOf(c[i]).equalsIgnoreCase(" ") == false && String.valueOf(c[i+1]).equalsIgnoreCase(" ") == true)
            {
            	sotu++;
            }
        }
        ch = "So tu co trong chuoi la: " + sotu + "\n";
        if(d1 != 0) ch += "So nguyen am u trong chuoi la: " + d1 + "\n";
        if(d2 != 0) ch += "So nguyen am e trong chuoi la: " + d2 + "\n";
        if(d3 != 0) ch += "So nguyen am o trong chuoi la: " + d3 + "\n";
        if(d4 != 0) ch += "So nguyen am a trong chuoi la: " + d4 + "\n";
        if(d5 != 0) ch += "So nguyen am i trong chuoi la: " + d5 + "\n";
		return ch;
	}
}

