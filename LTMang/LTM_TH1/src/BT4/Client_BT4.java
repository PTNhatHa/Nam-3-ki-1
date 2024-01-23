package BT4;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.*;
import javax.swing.*;


public class Client_BT4 extends JFrame  {

	TextArea output;
	JTextField input;
	static Socket socket;
	static int stt = 1;
	public static void main(String[] args) throws Exception  {
		try {
			socket = new Socket("localhost", 7000);
			Client_BT4 chat = new Client_BT4(stt);
			stt++;
			chat.setVisible(true);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void sendMessage() throws IOException
	{
		
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		String mess = input.getText();
		if(!mess.isEmpty())
		{
			try {
				dos.writeUTF(mess);
				dos.flush();
				//output.setText("");
	
			} catch (IOException e) {
				e.printStackTrace();
				output.setText("Thất bại");
			}	
		}
	}
	Client_BT4(int stt)
	{
		this.setTitle("Client");
		this.setSize(500, 300);
		this.setDefaultCloseOperation(3);
		this.setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		
		JPanel p = new JPanel();
		p.setLayout(new FlowLayout());
		JLabel lb = new JLabel("Nhập tên bảng ghi cần truy vấn: ");
		p.add(lb);
		input = new JTextField(20);
		p.add(input);
		JButton b1 = new JButton("Truy vấn");
		new Thread(new Runnable() {
            public void run() {
                try {
                	DataInputStream din = new DataInputStream(socket.getInputStream());
                    while(true) {
                    	String remess = din.readUTF();
        				output.setText(remess);
        				//input.setText("");
                        Thread.sleep(1000);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    output.setText("Gửi thất bại");
                } catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					output.setText("Gửi thất bại");
				}
            }
        }).start();	
		b1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				try {
					sendMessage();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		JButton b2 = new JButton("Close");
		b2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		p.add(b1);
		p.add(b2);
		this.add(p);
		
		output = new TextArea();
		output.setEditable(false);
		this.add(output);
	}
}
