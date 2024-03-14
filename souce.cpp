#include <iostream>
#include <Windows.h>
#include <math.h>
float pi = 3.14159;
int nScreenWidth = 120;
int nScreenHeight = 40;
float fPlayerX = 0.0f;
float fPlayerY = 0.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth =  16;
float fFOV = pi/4.0;
float fDepth = 16.0f;


using namespace std;
int main()
{
     // First create a screen buffer
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER,NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwByteWritten = 0;

    wstring map;
    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";

    while(1)
    {
       for(int x = 0; x < nScreenWidth;x++)
       {
            float fRayAngle = (fPlayerA - fFOV/2.0f) + ((float)x / (float)nScreenWidth)* fFOV;

            float fDistanceToWall = 0;
            bool bHitWall = false;
            
            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);
            
            while(!bHitWall && fDistanceToWall < fDepth )
            {
                fDistanceToWall += 0.1f;
                int nTestX =  (int)(fPlayerX + fEyeX + fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY + fDistanceToWall);

                if (nTestX < 0 or nTestX >= nMapWidth or nTestY >= nMapHeight)
                {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                }else{
                    
                    if (map[nTestY * nMapWidth + nTestX ] == '#')
                    {
                        bHitWall = true;
                    }
                }
            }

            //Calculate distance to ceiling and floor
            int nCeiling = (float)(nScreenHeight/2.0) - nScreenHeight/ (float)(fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

       }

        screen[nScreenWidth * nScreenHeight-1] = '0';
        WriteConsoleOutputCharacter(hConsole,screen, nScreenWidth * nScreenHeight,{0,0},&dwByteWritten);

    }
    return 0;
}