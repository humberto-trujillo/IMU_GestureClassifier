using System;
using UnityEngine;

public class IMU_GesturePrediction : MonoBehaviour
{
    SerialComm m_serialManager;
    IntPtr m_classifier;

    void Awake()
    {
        m_classifier = Classifier.NewShotClassifier();
    }

    void Start ()
    {
        m_serialManager = SerialComm.Instance as SerialComm;
        Debug.Log("GRT Version: " + Classifier.GrtVersion(m_classifier));
        Debug.Log("Loading classification model...");
        string filePath = "c:\\Users\\Humberto\\Documents\\Badminton_IMU\\Badminton_IMU\\DTWModel.txt";
        Debug.Log(Classifier.LoadModelFromFile(m_classifier,filePath) == 1? "Success" : "Failed!");
    }

    void Update()
    {
        string latestFrame = m_serialManager.ReturnData;
        if (latestFrame != null)
        {
            string[] tokens = m_serialManager.SplittedData();
            float x = float.Parse(tokens[1]);
            float y = float.Parse(tokens[2]);
            float z = float.Parse(tokens[3]);

            Classifier.AddToTimeSeriesBuffer(m_classifier, x, y, z);
        }
    }
}
