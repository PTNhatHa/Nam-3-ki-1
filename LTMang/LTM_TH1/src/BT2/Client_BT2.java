package BT2;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;
import javax.swing.*;;


public class Client_BT2 extends JFrame {
	private TextArea input, output;
	private static Socket clientSocket;
	private static DataInputStream din;
	private static DataOutputStream dos;
	
	private static void connectServer()
	{
		try {
			clientSocket = new Socket("localhost", 7000);
			din = new DataInputStream(clientSocket.getInputStream());
			dos = new DataOutputStream(clientSocket.getOutputStream());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private void sendMessage()
	{
		connectServer();
		String mess = input.getText();
		if(!mess.isEmpty())
		{
			try {
				dos.writeUTF(mess);
				dos.flush();
				
				new Thread(new Runnable() {
	                public void run() {
	                    try {
	                        while(true) {
	                        	String remess = din.readUTF();
	            				output.setText(mess + "\n" + output.getText() + "\n" + remess);
	            				input.setText("");
		                        Thread.sleep(1000);
	                        }
	                    } catch (IOException e) {
	                        e.printStackTrace();
	                    } catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
	                }
	            }).start();	
				
			} catch (IOException e) {
				e.printStackTrace();
			}	
		}
	}
	Client_BT2()
	{
		this.setTitle("Client");
		this.setSize(500, 500);
		this.setDefaultCloseOperation(3);
		this.setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		
		JLabel t1 = new JLabel("Output");
		this.add(t1);
		output = new TextArea();
		output.setEditable(false);
		this.add(output);
		JLabel t2 = new JLabel("Input");
		this.add(t2);
		input = new TextArea();
		this.add(input);
		JButton b = new JButton("Send");
		b.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				sendMessage();
			}
		});
		this.add(b);
		setVisible(true);
	}
	public static void main(String[] args) throws Exception 
	{
		new Client_BT2();
	}
	
}
