using System;
using System.Runtime.InteropServices;

class Program
{
    [StructLayout(LayoutKind.Sequential)]
    public struct SYSTEMTIME
    {
        public ushort Year;
        public ushort Month;
        public ushort DayOfWeek;
        public ushort Day;
        public ushort Hour;
        public ushort Minute;
        public ushort Second;
        public ushort Milliseconds;
    }

    [DllImport("kernel32.dll")]
    public static extern void GetLocalTime(out SYSTEMTIME time);

    static void Main(string[] args)
    {
        SYSTEMTIME currentTime;
        GetLocalTime(out currentTime);

        DateTime currentDateTime = new DateTime(currentTime.Year, currentTime.Month,
                        currentTime.Day, currentTime.Hour, currentTime.Minute, currentTime.Second);

        Console.WriteLine("Thoi gian hien tai: " + currentDateTime.ToString("yyyy-MM-dd HH:mm:ss"));
    }
}
