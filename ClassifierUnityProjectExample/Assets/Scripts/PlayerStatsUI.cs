using UnityEngine;
using UnityEngine.UI;

public class PlayerStatsUI : MonoBehaviour
{
    public Text smashCounterText;
    public Text dropCounterText;
    public Text forehandCounterText;
    public Text backhandCounterText;

    IMU_GesturePrediction m_imu;
    

    private void Start()
    {
        m_imu = FindObjectOfType<IMU_GesturePrediction>() as IMU_GesturePrediction;
        if (m_imu != null)
        {
            m_imu.PredictionUpdateEvent += UpdateCounters;
        }
    }

    void UpdateCounters(int smash, int drop, int fh, int bh)
    {
        smashCounterText.text = smash.ToString();
        dropCounterText.text = drop.ToString();
        forehandCounterText.text = fh.ToString();
        backhandCounterText.text = bh.ToString();
    }
}
