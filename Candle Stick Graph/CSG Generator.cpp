#include <iostream>
#include "CSG.h"
#include "Logger.h"
using namespace std;

char infile[100] = "intc_us_data.csv";
char outfile[100] = "chart.txt";
char logstr[100];
CSG csg;
Logger logger("programlog.log");

void ClearScreen()
{
    system("cls");
}

void WaitForEnter()
{
    cin.ignore();
    cin.get();
}

void input_error()
{
    cout << "Inproper input!\n";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    WaitForEnter();
}

void menu_change_input()
{
    ClearScreen();

    cout << "New input file: ";
    cin >> infile;
    cout << "Input file has been changed succesfully!";
    WaitForEnter();
}

void menu_change_output()
{
    ClearScreen();

    cout << "New output file: ";
    cin >> outfile;
    cout << "Output file has been changed succesfully!";
    WaitForEnter();
}

void menu_change_height()
{
    ClearScreen();

    int input = 0;
    cout << "Enter new height: ";
    cin >> input;
    if (!cin)
    {
        input_error();
        return;
    }

    csg.SetHeight(input);
    cout << "Height has been change succesfully!";
    WaitForEnter();
}

void menu_load_file()
{
    ClearScreen();
    csg.LoadFromFile(infile);
    cout << "File has been sucessfully loaded!";
    WaitForEnter();
}

void menu_save_file()
{
    ClearScreen();
    csg.SaveToFile(outfile);
    cout << "Graph has been succesfully saved!";
    WaitForEnter();
}

void menu_change_grouping()
{
    int input = -1;
    ClearScreen();
    cout << "Choose grouping: \n"
        << "1. Day\n"
        << "2. Week\n"
        << "3. Month\n\n";
    cin >> input;
    if (!cin)
    {
        input_error();
        return;
    }

    switch (input)
    {
    case 1:
        csg.SetGrouping(GraphGrouping::DAY);
        break;
    case 2:
        csg.SetGrouping(GraphGrouping::WEEK);
        break;
    case 3:
        csg.SetGrouping(GraphGrouping::MONTH);
        break;
    default:
        cout << "Inproper input!";
        WaitForEnter();
        return;
    }

    cout << "Grouping has been set succesfully!";
    WaitForEnter();
}

void menu_change_time()
{
    int input = -1;
    ClearScreen();
    cout << "Choose time range:\n"
        << "1. Begin\n"
        << "2. End\n";

    cin >> input;
    if (!cin)
    {
        input_error();
        return;
    }

    tm time{ 0 };
    ClearScreen();
    tm time_begin = csg.GetTimeBegin();
    tm time_end = csg.GetTimeEnd();
    cout << "Input Time YYYY-MM-DD\n";
    cin >> get_time(&time, "%Y-%m-%d");
    
    switch (input)
    {
    case 1:
    {
        if (mktime(&time_end) < mktime(&time))
        {
            cout << "Begin time is bigger than End time!";
            WaitForEnter();
            return;
        }
        csg.SetTimeBegin(time);
        break;
    }
    case 2:
    {
        if (mktime(&time_begin) > mktime(&time))
        {
            cout << "End time is smaller than Begin time!";
            return;
        }
        csg.SetTimeEnd(time);
        break;
    }
    default:
        break;
    }
}

void menu_draw_slice()
{
    const int width_max = 200;
    const int height_max = 50;

    int height = -1;
    int width = -1;
    int group = -1;
    GraphGrouping grouping = GraphGrouping::DAY;
    tm time_begin{ 0 }, time_end{ 0 };
    ClearScreen();
    cout << "Width [max "<<width_max<<"]: ";
    cin >> width;

    if (!cin || width > width_max || width <=0)
    {
        input_error();
        return;
    }

    cout << "Height [max" << height_max << "]: ";
    cin >> height;

    if (!cin || height > height_max || height <=0)
    {
        input_error();
        return;
    }

    cout << "Time range begin [YYYY-MM-DD]:\n";
    cin >> get_time(&time_begin, "%Y-%m-%d");
    cout << "Time range end [YYYY-MM-DD]:\n";
    cin >> get_time(&time_end, "%Y-%m-%d");

    if (mktime(&time_begin) > mktime(&time_end))
    {
        cout << "Improper time interval!";
        WaitForEnter();
        return;
    }

    cout << "Grouping: \n"
        << "1. Day\n"
        << "2. Week\n"
        << "3. Month\n\n";

    cin >> group;

    if (!cin || group > 3 || group <=0)
    {
        input_error();
        return;
    }

    switch (group)
    {
    case 1:
        grouping = GraphGrouping::DAY;
        break;
    case 2:
        grouping = GraphGrouping::WEEK;
        break;
    case 3:
        grouping = GraphGrouping::MONTH;
        break;
    }

    csg.DrawSlice(height, width, time_begin, time_end, grouping);
    WaitForEnter();
}


int main()
{
    logger.WriteLine("Program Start");

    int input = -1;
    char time_buffer_begin[50], time_buffer_end[50];//used to show begin and end time range
    while (true)
    {
        ClearScreen();

        tm time_begin = csg.GetTimeBegin();
        tm time_end = csg.GetTimeEnd();

        strftime(time_buffer_begin, sizeof(time_buffer_begin), "%Y-%m-%d", &time_begin);
        strftime(time_buffer_end, sizeof(time_buffer_end), "%Y-%m-%d", &time_end);

        cout << setw(15) << "Input:\t[" << infile << "]\n"
            << setw(15) << "Output:\t[" << outfile << "]\n"
            << setw(15) << "Candles:\t[" << csg.GetCandleCount() << "]\n"
            << setw(15) << "Width:\t[" << csg.GetGraphWidth() << "]\n"
            << setw(15) << "Height:\t[" << csg.GetGraphHeight() << "]\n"
            << setw(15) << "Grouping:\t[" << GroupToString(csg.GetGrouping()) << "]\n"
            << setw(15) << "Begin:\t[" << time_buffer_begin << "]\n"
            << setw(15) << "End:\t[" << time_buffer_end << "]\n\n\n";

        cout << "1. Change input file\n"
            << "2. Change output file\n"
            << "3. Change Height\n"
            << "4. Change Grouping\n"
            << "5. Change Time Range\n"
            << "6. Show Graph Slice\n"
            << "7. Load\n"
            << "8. Save\n"
            << "0. Exit\n";

        cin >> input;
        if (!cin)
            input_error();

        switch (input)
        {
        case 1:
            menu_change_input();
            sprintf_s(logstr, sizeof(logstr), "Changed input to: %s", infile);
            logger.WriteLine(logstr);
            break;
        case 2:
            menu_change_output();
            sprintf_s(logstr, sizeof(logstr), "Changed output to: %s", outfile);
            logger.WriteLine(logstr);
            break;
        case 3:
            menu_change_height();
            sprintf_s(logstr, sizeof(logstr), "Changed graph height to: %d", csg.GetGraphHeight());
            logger.WriteLine(logstr);
            break;
        case 4:
            menu_change_grouping();
            sprintf_s(logstr, sizeof(logstr), "Changed grouping to: %s", GroupToString(csg.GetGrouping()));
            logger.WriteLine(logstr);
            break;
        case 5:
            menu_change_time();
            logger.WriteLine("Changed time range");
            break;
        case 6:
            menu_draw_slice();
            logger.WriteLine("Draw Slice");
            break;
        case 7:
            sprintf_s(logstr, sizeof(logstr), "%s %s", "Loaded File:", infile);
            logger.WriteLine(logstr);
            menu_load_file();
            break;
        case 8:
            sprintf_s(logstr, sizeof(logstr), "%s %s", "Saved File:", outfile);
            logger.WriteLine(logstr);
            menu_save_file();
            break;
        case 0:
            logger.WriteLine("Program exit\n\n");
            return 0;
        default:
            cout << "Inproper input !";
            logger.WriteLine("Inproper input");
            WaitForEnter();
            break;
        }
    }
}

