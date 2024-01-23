package BT4;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.*;
import com.mysql.cj.jdbc.*;

public class CSDLServer {

	public static void main(String[] args) throws SQLException, IOException {
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			String url = "jdbc:mysql://localhost:3306/dulieu1";
			String user = "root";
			String password = "";
			Connection cnt = (Connection) DriverManager.getConnection(url, user, password);
			System.out.println("Kết nối thành công");
			
			String query = "SELECT * FROM table1";
			Statement st = cnt.createStatement();
			ResultSet rs = st.executeQuery(query);
			String msg = "MSSV\t\tHọ tên\t\tNgày sinh \tNghề Nghiệp\n";
			while(rs.next())
			{
				msg += rs.getString(1) + " \t" + rs.getString(2) + " \t" + rs.getString(3) + "\t" + rs.getString(4) + "\n";
			}
			
			ServerSocket server = new ServerSocket(7002);
			System.out.println("Server is started");
			Socket socket = server.accept();
			DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
			dos.writeUTF(msg);
			dos.flush();
			
		} catch (ClassNotFoundException e1) {
			System.out.println("Lỗi");
			e1.printStackTrace();
		}
	}

}
