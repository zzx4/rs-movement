#include "funcs.h"

int main( )
{
    int laps = 0;
    HWND console = GetConsoleWindow( );
    std::thread esc( escape );

    if ( console )
    {
        SetWindowPos( console, HWND_NOTOPMOST, 0, 0, 220, 480, SWP_DRAWFRAME | SWP_SHOWWINDOW );
        SetConsoleTitleA( "awawa" );
    }

    //Sleep( 10000 );

    std::array< int, 2 > initial = getpos( );
    std::array< int, 2 > start = getpos( );

    while ( true )
    {
        //seers( );
        //seers_box( &laps, start, initial );
        //ardy( &laps, start, initial );
        //correct( laps, start, initial );
        //glassmake( &laps, start, initial );
        //giga_wait( );
        //drop_inv( );
        //plank( &laps );

        //cape( );
        brimhaven( );
        Sleep( 1 );
    }

    esc.join( );
}