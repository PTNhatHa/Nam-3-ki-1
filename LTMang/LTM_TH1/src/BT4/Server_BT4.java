package BT4;

import java.io.*;
import java.net.*;
import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class Server_BT4 {

	public static void main(String[] args) throws SQLException, IOException {
		ServerSocket socketServer = new ServerSocket(7000);
		System.out.println("Server is started");
		int count = 1;
		while(true)
		{
			Socket socket = socketServer.accept();
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
				String str = din.readUTF();
				
				Class.forName("com.mysql.cj.jdbc.Driver");
				String url = "jdbc:mysql://localhost:3306/dulieu";
				String user = "root";
				String password = "";
				Connection cnt = (Connection) DriverManager.getConnection(url, user, password);
				
				String query = "SELECT * FROM " + str;
				Statement st = cnt.createStatement();
				ResultSet rs = st.executeQuery(query);
				
				ResultSetMetaData rsmd = rs.getMetaData();
				int columnCount = rsmd.getColumnCount();
				String msg = "";
//				for (int i = 1; i <= columnCount; i++) {
//				    String name = rsmd.getColumnName(i);
//				    msg += name + " \t\t";
//				}
//				msg += "\n";
				while(rs.next())
				{
					for (int i = 1; i <= columnCount; i++) 
					{
					    msg += rs.getObject(i) + "\t";
					}
					msg += "\n";
				}
				dos.writeUTF(msg);
				dos.flush();
			}
		} catch (IOException e) {
			e.printStackTrace();	
		} catch (ClassNotFoundException e) {
			e.printStackTrace();	
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}
