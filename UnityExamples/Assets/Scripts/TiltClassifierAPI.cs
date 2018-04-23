using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TiltClassifierAPI
{
	[DllImport("IMU_GestureClassifier")]
	public static extern double GrtVersion();

	[DllImport("IMU_GestureClassifier")]
	public static extern int PredictTilt(string modelFilePath, double x, double y, double z);
}
