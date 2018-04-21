using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class IMU_TextLogControl : MonoBehaviour
{
    public GameObject textLogItemPrefab;
    public Transform contentHolder;
    public int entriesLimit = 20;
    SerialComm m_serialManager;
    string latestEntry = "";
    List<GameObject> textEntries = new List<GameObject>();
    

    void Start()
    {
        m_serialManager = SerialComm.Instance as SerialComm;
    }

    void LogText(string newItemText)
    {
        GameObject newEntry = Instantiate(textLogItemPrefab, contentHolder) as GameObject;
        newEntry.GetComponent<Text>().text = newItemText;
        textEntries.Add(newEntry);
        if (textEntries.Count >= entriesLimit)
        {
            GameObject firstEntry = textEntries[0];
            textEntries.Remove(firstEntry);
            Destroy(firstEntry.gameObject);
        }
    }

    private void Update()
    {
        string latestFrame = m_serialManager.ReturnData;
        if (latestFrame != null)
        {
            if (latestFrame != latestEntry)
            {
                latestEntry = latestFrame;
                LogText(latestEntry);
            }
        }
    }
}
