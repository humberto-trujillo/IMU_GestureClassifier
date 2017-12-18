using System;
using System.Text;
using UnityEngine;

public class IMU_GesturePrediction : MonoBehaviour
{
    SerialComm m_serialManager;
    IntPtr m_predict;

    void Awake()
    {
        m_predict = Classifier.DllNewShotPredict();
        //if(m_predict == null)
        //{
        //    Destroy(this);
        //}
    }
    void Start ()
    {
        m_serialManager = SerialComm.Instance as SerialComm;
        Debug.Log("Version: " + Classifier.DllGrtVersion(m_predict));
    }
	
	void Update ()
    {
        string[] tokens = m_serialManager.SplittedData();
        float x = float.Parse(tokens[1]);
        float y = float.Parse(tokens[2]);
        float z = float.Parse(tokens[3]);

        Classifier.DllAddToTimeSeriesBuffer(m_predict, x,y,z);
        if (Input.GetKeyDown(KeyCode.D))
        {
            StringBuilder sb = new StringBuilder(200);
            Classifier.DllGetBufferAsString(m_predict, sb, sb.Capacity);
            Debug.Log("Desde dll: \n"+sb.ToString());
        }
    }
}
