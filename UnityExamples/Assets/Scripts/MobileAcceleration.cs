using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

[System.Serializable]
public struct SampleEntry
{
	public int label;
	public Vector3 accel;

	public SampleEntry(int l, Vector3 a)
	{
		label = l;
		accel = a;
	}
}
public class MobileAcceleration : MonoBehaviour 
{
	public int currentLabel = 1;
	public bool isRecording;
	[Range(0.05f,3f)]
	public float samplingRate;
	public List<SampleEntry> samples = new List<SampleEntry> ();

	void Start () 
	{
		StartCoroutine(RecordSamplesCourutine());	
	}
	void Update () 
	{
		
	}

	IEnumerator RecordSamplesCourutine()
	{
		while (true)
		{
			if (isRecording) 
			{
				SampleEntry newEntry = new SampleEntry(currentLabel,Input.acceleration);
				samples.Add (newEntry);
				yield return new WaitForSeconds(samplingRate);
			}
			yield return null;
		}
	}

	public void SaveTrainingDataToFile()
	{
		StreamWriter writer = new StreamWriter(Application.dataPath + "/Samples.txt");
		foreach (var s in samples) 
		{
			string line = s.label + "\t" + s.accel.x + "\t" + s.accel.y + "\t" + s.accel.z;
			writer.WriteLine (line);	
		}
		writer.Close();
		Debug.Log ("File Saved to "+Application.dataPath );
	}

	public void IncreaseLabel()
	{
		currentLabel++;
	}

}
