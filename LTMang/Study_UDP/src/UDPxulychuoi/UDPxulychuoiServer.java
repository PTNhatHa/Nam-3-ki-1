package UDPxulychuoi;

import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class UDPxulychuoiServer {

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
		// u e o a i
		int d1=0, d2=0, d3=0, d4=0, d5=0;
        for(int i = 0; i < c.length; i++) 
        {
        	if(String.valueOf(c[i]).equalsIgnoreCase("u")) d1++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("e")) d2++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("o")) d3++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("a")) d4++;
        	if(String.valueOf(c[i]).equalsIgnoreCase("i")) d5++;
        }
        String[] substring = s.split("\\s+");
        int sotu = substring.length;
        ch = "So tu co trong chuoi la: " + sotu + "\n";
        if(d1 != 0) ch += "So nguyen am u trong chuoi la: " + d1 + "\n";
        if(d2 != 0) ch += "So nguyen am e trong chuoi la: " + d2 + "\n";
        if(d3 != 0) ch += "So nguyen am o trong chuoi la: " + d3 + "\n";
        if(d4 != 0) ch += "So nguyen am a trong chuoi la: " + d4 + "\n";
        if(d5 != 0) ch += "So nguyen am i trong chuoi la: " + d5 + "\n";
		return ch;
	}
	public static void main(String[] args) throws IOException 
	{
		// Gán cổng
		DatagramSocket serverSocket = new DatagramSocket(7000);
		// Gửi nhận dl byte
		System.out.println("Server is started");
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];
		while(true)
		{
			// Tạo gói nhận dl
			DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
			// Nhận dl từ Client
			serverSocket.receive(receivePacket);
			// Lấy IP của Client
			InetAddress IPAddress = receivePacket.getAddress();
			// Lấy port của Client
			int port = receivePacket.getPort();
			// Chuyển dl thành string để xl
			String request = new String(receivePacket.getData(), 0, receivePacket.getLength());
			System.out.println(request);
			// Xử lí dl
			String msg = chuoinguoc(request) + "\n" 
					+ chuthuong(request) + "\n" + chuhoa(request) + "\n" + hoathuong(request) + "\n"
					+ demtu(request) + "\n";
			sendData = msg.getBytes();
			DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
			System.out.println(port);
			serverSocket.send(sendPacket);
		}
	}
}


