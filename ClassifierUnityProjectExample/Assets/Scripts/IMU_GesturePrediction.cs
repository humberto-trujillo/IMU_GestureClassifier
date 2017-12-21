using System;
using System.Collections;
using UnityEngine;

public class IMU_GesturePrediction : MonoBehaviour
{
    public delegate void OnPredictionUpdate(int smash, int drop, int fh, int bh);
    public event OnPredictionUpdate PredictionUpdateEvent;

    SerialComm m_serialManager;
    IntPtr m_classifier;

    int[] m_classCounters;

    void Awake()
    {
        m_classifier = Classifier.NewShotClassifier();
        m_classCounters = new int[4];
    }

    void Start ()
    {
        m_serialManager = SerialComm.Instance as SerialComm;
        Debug.Log("GRT Version: " + Classifier.GrtVersion(m_classifier));
        string filePath = Application.dataPath + "/Resources/DTWModel.txt";
        Debug.Log("Loading classification model..."+ 
            (Classifier.LoadModelFromFile(m_classifier,filePath) == 1? "Success" : "Failed!"));

         StartCoroutine(PredictionRoutine());
    }

    void Update()
    {
        string latestFrame = m_serialManager.ReturnData;
        if (latestFrame != null)
        {
            string[] tokens = m_serialManager.SplittedData();
            float x = float.Parse(tokens[0]);
            float y = float.Parse(tokens[1]);
            float z = float.Parse(tokens[2]);
            Debug.Log("X: "+x+ " Y: "+y+" Z: "+z);
            Classifier.AddToTimeSeriesBuffer(m_classifier, x, y, z);
        }
    }

    IEnumerator PredictionRoutine()
    {
        yield return new WaitForSeconds(2f);
        while (true)
        {
            int prediction = Classifier.Predict(m_classifier);
            if (prediction == 0)
            {
                continue;
            }
            m_classCounters[prediction-1]++;
            if (PredictionUpdateEvent != null)
            {
                PredictionUpdateEvent(m_classCounters[0], m_classCounters[1], m_classCounters[2], m_classCounters[3]);
            }
            yield return new WaitForSeconds(1);
        }
    }
}
