using UnityEngine;
using System.IO.Ports;

public class SerialComm : IMU_Communication
{
    public string port = "COM3"; //When using MacOS -> "/dev/cu.usbmodem1411"
    SerialPort m_stream;

	void Start () 
	{
        m_stream = new SerialPort(port, 9600);
        InitComm();
	}
    
	public override void FetchData()
	{
        base.FetchData();
		Debug.Log ("Starting Serial COMM Thread!");
		m_stream.Open();
		Debug.Log ("Serial port "+ port + " Open!");
		while (true)
		{
            if (!m_stream.IsOpen)
            {
                break;
            }
            m_returnData = m_stream.ReadLine();
            //Debug.Log(m_returnData);
			if (m_returnData != null) 
			{
                if (m_returnData.StartsWith("{"))
                {
                    OnCalibrationReceived(m_returnData);
                }
				m_stream.BaseStream.Flush();
			}
		}
	}

    public override void OnCommTerminate()
    {
        base.OnCommTerminate();
        m_stream.Close();
        Debug.Log("Serial port "+ port +" closed!");
    }
}
