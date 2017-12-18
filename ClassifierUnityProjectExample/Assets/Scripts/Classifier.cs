using System.Runtime.InteropServices;
using System;
using System.Text;

public class Classifier
{
    [DllImport("Badminton_Shot_Classifier")]
    public static extern IntPtr NewShotClassifier();

    [DllImport("Badminton_Shot_Classifier")]
    public static extern double GrtVersion(IntPtr obj);

    [DllImport("Badminton_Shot_Classifier")]
    public static extern void AddToTimeSeriesBuffer(IntPtr obj, double x, double y, double z);

    [DllImport("Badminton_Shot_Classifier")]
    public static extern void GetBufferAsString(IntPtr obj, StringBuilder str, int len);

    [DllImport("Badminton_Shot_Classifier")]
    public static extern int LoadModelFromFile(IntPtr obj, string filePath);

    [DllImport("Badminton_Shot_Classifier")]
    public static extern int Predict(IntPtr obj);

    //public static IntPtr m_predict;

	//void Start ()
 //   {
 //       m_predict = DllNewShotPredict();
 //       Debug.Log("Version: "+ DllGrtVersion(m_predict));
 //   }
	
	//void Update ()
         
 //   {
 //       if (Input.GetKeyDown(KeyCode.A))
 //       {
 //           DllAddToTimeSeriesBuffer(m_predict, 0.05f, 0.06f, 0.7f);
 //       }
 //       if (Input.GetKeyDown(KeyCode.D))
 //       {
 //           StringBuilder sb = new StringBuilder(200);
 //           DllGetBufferAsString(m_predict, sb, sb.Capacity);
 //           Debug.Log(sb.ToString());
 //       }
 //       if (Input.GetKeyDown(KeyCode.C))
 //       {
 //           string path = "c:\\Users\\Humberto\\Documents\\Badminton_IMU\\Badminton_IMU\\DTWModel.txt";
 //           Debug.Log(DllLoadModelFromFile(m_predict, path));
 //       }
 //   }
}
