#pragma once

#include <iostream>
#include <thread>
#include <cmath>
#include <Windows.h>
#include <array>
#include <string>
#include <vector>
#include <ctime>
#include <dinput.h>


#include "data.h"

void move( int x, int y )
{
	mouse_event( MOUSEEVENTF_MOVE, 2 * x, -2 * y, 0, 0 );
	//accounts for windows mouse settings, y inverted
}

void scroll( int amount )
{
	mouse_event( MOUSEEVENTF_WHEEL, 0, 0, amount, 0 );
	Sleep( rand( ) % 42 + 170 );
}

void click( )
{
	Sleep( rand( ) % 100 + 50 );
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep( rand( ) % 100 + 50 );
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void click2( int x, int y )
{
	Sleep( rand( ) % 25 + 30 );
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	move( x, y );
	Sleep( rand( ) % 25 + 50 );
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void send_input( WORD key )
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	//input.ki.wVk = VK_OEM_6;
	input.ki.wVk = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	input.ki.wScan = key;

	SendInput( 1, &input, sizeof( input ) );
	Sleep( rand( ) % 10 + 65 );
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput( 1, &input, sizeof( input ) );
}

double bezier( int p_0, int p_1, int p_2, int p_3, double t )
{
	return pow( ( 1 - t ), 3 ) * p_0 + ( 3 * pow( (1 - t), 2 ) * t * p_1 ) + ( 3 * ( 1 - t ) * pow( t, 2 ) * p_2 ) + ( pow( t, 3 ) * p_3 );
}

bool pressing( unsigned const vk_code )
{
	return 0 != GetAsyncKeyState( vk_code );
}

void escape( )
{
	while ( true )
	{
		if ( pressing( VK_F7 ) ) {
			std::cout << "exiting" << std::endl;
			exit( 0 );
		}
		Sleep( 500 );
	}

}

void giga_wait( )
{
	if ( rand( ) % 86 == 56 )
	{
		std::cout << "giga waiting lole" << std::endl;
		Sleep(26526);
	}
}

std::array< int, 2 > getpos( )
{
	POINT pt;
	GetCursorPos( &pt );
	std::array< int, 2 > start = { pt.x, pt.y };
	return start;
}

void correct( int lap, std::array< int, 2 > &start, std::array< int, 2 > &initial )
{
	if ( lap % 2 == 0 )
	{
		std::array< int, 2 > current = getpos( );
		if ( lap % 9 == 0 )
			move( initial[0] - current[0], current[1] - initial[1] );
		else
			move( start[0] - current[0], current[1] - start[1] );
		//std::cout << "current x: " << current[0] << " starting x: " << start[0] << std::endl;
		//std::cout << "current y: " << current[1] << " starting y: " << start[1] << std::endl;
		//std::cout << "moved x: " << start[0] - current[0] << " moved y: " << start[1] - current[1] << std::endl;
		current = getpos( );
		start = { current[0], current[1] };
	}
}

std::array< int, 2> gen( std::array< int, 2 > p_3 )
{
	std::array< int, 2 > pt { };

	if ( std::abs( p_3[0] ) == 0)
		pt = { 0, rand() % std::abs(p_3[1]) };
	if ( std::abs( p_3[1] ) == 0)
		pt = { rand() % std::abs(p_3[0]), 0 };
	if ( std::abs( p_3[0] ) != 0 && std::abs( p_3[1] ) != 0 )
		//pt = { rand() % std::abs(p_3[0]), rand() % std::abs(p_3[1])};
		pt = { rand( ) % 120 + 50, rand( ) % 90 + 50 };

	if ( p_3[0] < 0)
		pt[0] = pt[0] * -1;
	if ( p_3[1] < 0)
		pt[1] = pt[1] * -1;

	return pt;
}

std::array< int, 2> gen_small( std::array< int, 2 > p_3 )
{
	std::array< int, 2 > pt { };

	if ( std::abs( p_3[0] ) == 0)
		pt = { 0, rand() % std::abs(p_3[1]) };
	if ( std::abs( p_3[1] ) == 0)
		pt = { rand() % std::abs(p_3[0]), 0 };
	//if ( std::abs( p_3[0] ) != 0 && std::abs( p_3[1] ) != 0 )
		//pt = { rand() % std::abs(p_3[0]), rand() % std::abs(p_3[1])};
	pt = { rand( ) % 10 + 12, rand( ) % 10 + 11 };

	if ( p_3[0] < 0)
		pt[0] = pt[0] * -1;
	if ( p_3[1] < 0)
		pt[1] = pt[1] * -1;

	return pt;
}

void brimhaven( )
{
	bool held = false;
	int sleep_t;
	int var_x;
	int var_y;
	
	srand( time( NULL ) );

	if ( !held )
	{
		while ( !pressing( VK_XBUTTON2 ) )
			Sleep( 1 );
		held = true;
	}

	std::cout << "starting" << std::endl;

	while ( held )
	{
		var_x =  rand( ) % 3 - 1;
		var_y =  rand( ) % 3 - 1;
		click2( var_x, var_y );
		sleep_t = ( rand( ) % 500 + 986 );
		Sleep( sleep_t );
		if ( pressing( VK_XBUTTON2 ) )
			held = false;
	}

	std::cout << "ending" << std::endl;
}

void cape( )
{
	bool held = false;
	int sleep_t;

	srand( time( NULL ) );

	if ( !held )
		while ( !pressing( VK_XBUTTON2 ) )
			Sleep( 1 );

	for ( int i = 0; i < 6; i++ )
	{
		click( );
		Sleep( rand( ) % 60 + 606 );
		send_input( DIKEYBOARD_4 );
		Sleep( rand( ) % 60 + 1200 );
		click( );
		Sleep( rand( ) % 60 + 606 );
		send_input( DIKEYBOARD_1 );
		Sleep( rand( ) % 60 + 606 );
	}


	sleep_t = ( rand() % 71 + 11 );
	Sleep( sleep_t );

	held = false;

	return;
}

void plank( int * laps )
{
	bool held = false;
	double x = 0;
	double x_prev = 0;
	double y = 0;
	double y_prev = 0;
	double x_move;
	double y_move;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	std::array< int, 2> p_0 { };
	std::array< int, 2> p_3 { };
	std::array< int, 2> p_1 { };
	std::array< int, 2> p_2 { };
	std::array< int, 2 > current { };
	std::array< int, 2> var = { 0, 0 };

	srand( time( NULL ) );

	p_0 = { 0, 0 };
	p_3 = { 72 - var[0], -114 - var[1] };

	p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
	p_1 = gen_small( p_3 );
	p_2 = gen_small( p_3 );

	x = 0;
	y = 0;
	x_prev = 0;
	y_prev = 0;
	inc_x = 0;
	inc_y = 0;

	if ( !held )
		while ( !pressing( VK_XBUTTON2 ) )
			Sleep( 1 );

	click( );
	Sleep( rand( ) % 100 + 1010 );
	send_input( DIKEYBOARD_F9 );
	Sleep( rand( ) % 100 + 2310 );

	for (double t = 0; t < 1; t += 0.05)
	{
		x_prev = x;
		y_prev = y;

		x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
		y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

		x_move = x - x_prev + 0.5;
		y_move = y - y_prev + 0.5;

		inc_x += int ( x_move );
		inc_y += int ( y_move );


		move( int ( x_move ), int ( y_move ) );

		sleep_t = rand() % 7 + 3;

		Sleep( sleep_t );
	}

	move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );

	click( );
	Sleep( rand( ) % 52 + 604 );
	click( );
	Sleep( rand( ) % 50 + 601 );
	if ( *laps % 8 == 0 ) {
		send_input( DIKEYBOARD_SPACE );
		Sleep( rand( ) % 80 + 600 );
		send_input( DIKEYBOARD_1 );
		Sleep( rand( ) % 100 + 601 );
		send_input( DIKEYBOARD_SPACE );
		Sleep( rand( ) % 100 + 605 );
	}
	send_input( DIKEYBOARD_1 );
	Sleep( rand( ) % 45 + 604 );
	send_input( DIKEYBOARD_SPACE );
	Sleep( rand( ) % 45 + 608 );
	send_input( DIKEYBOARD_1 );
	Sleep( rand( ) % 40 + 601 );
	send_input( DIKEYBOARD_SPACE );
	Sleep( rand( ) % 30 + 601 );
	send_input( DIKEYBOARD_F3 );

	p_0 = { 0, 0 };
	p_3 = { 5 - var[0], 114 - var[1] };

	p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
	p_1 = gen_small( p_3 );
	p_2 = gen_small( p_3 );

	x = 0;
	y = 0;
	x_prev = 0;
	y_prev = 0;
	inc_x = 0;
	inc_y = 0;

	for (double t = 0; t < 1; t += 0.05)
	{
		x_prev = x;
		y_prev = y;
		y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

		x_move = x - x_prev + 0.5;
		y_move = y - y_prev + 0.5;

		inc_x += int ( x_move );
		inc_y += int ( y_move );


		move( int ( x_move ), int ( y_move ) );

		sleep_t = rand() % 7 + 3;

		Sleep( sleep_t );
	}

	move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );

	click( );

	sleep_t = ( rand() % 71 + 11 );
	Sleep( sleep_t );

	held = false;

	* laps = * laps + 1;
	std::cout << "laps completed: " << * laps << std::endl;

	return;
}

void correct_old( std::array< int, 2> pt, int inc_x, int inc_y )
{
	double x_prev = 0;
	double y_prev = 0;
	double x = 0;
	double y = 0;
	std::array< int, 2> p_0 = { 0, 0 };
	std::array< int, 2> p_3 = { pt[0] - inc_x, pt[1] - inc_y };
	std::array< int, 2>p_1 = gen( p_3 );
	std::array< int, 2> p_2 = gen( p_3 );
	double lost_x = 0;
	double lost_y = 0;
	int casted_x;
	int casted_y;
	double x_move;
	double y_move;
	int sleep_t;

	for (double t = 0; t < 1; t += 0.5)
	{
		x_prev = x;
		y_prev = y;

		x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
		y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

		x_move = x - x_prev + 0.5;
		y_move = y - y_prev + 0.5;

		casted_x = int ( x_move );
		casted_y = int ( y_move );
		lost_x += ( x_move - casted_x );
		lost_y += ( y_move - casted_y );

		//std::cout << x << " " << x_prev << " " << x_move << " " << casted_x << " " << lost_x << "\n";
		std::cout << "x move: " << x_move << " y move: " << y_move << std::endl;

		move( int ( x_move ), int ( y_move ) );

		sleep_t = rand() % 7 + 3;

		Sleep( sleep_t );
	}

	if (std::abs(lost_x) > 0.5)
		move(int (lost_x +0.5), 0);
	if (std::abs(lost_y) > 0.5)
		move( 0, int (lost_y + 0.5) );
}

void seers( )
{
	double x = 0;
	double x_prev = 0;
	double y = 0;
	double y_prev = 0;
	double x_move;
	double y_move;
	int casted_x;
	int casted_y;
	double lost_x = 0;
	double lost_y = 0;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x;
	int var_y;
	std::array< int, 2> p_0;
	std::array< int, 2> p_3;
	std::array< int, 2> p_1;
	std::array< int, 2> p_2;

	srand( time( NULL ) );


	for ( int i = 0; i < 7; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { px_seers[i][0], px_seers[i][1] };
		p_1 = gen( p_3 );
		p_2 = gen( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		lost_x = 0;
		lost_y = 0;
		inc_x = 0;
		inc_y = 0;
		//std::cout << "i: " << i << "\n\n";

		for (double t = 0; t < 1; t += 0.05)
		{
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			casted_x = int ( x_move );
			casted_y = int ( y_move );
			lost_x += ( x_move - casted_x );
			lost_y += ( y_move - casted_y );
			inc_x += casted_x;
			inc_y += casted_y;

			//std::cout << x << " " << x_prev << " " << x_move << " " << casted_x << " " << lost_x << "\n";

			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 7 + 3;

			Sleep( sleep_t );
		}

		std::cout << "i: " << i << " " << px_seers[i][0] << " " << px_seers[i][1] << "\n";
		//std::cout << "moved x: " << inc_x << " moved y: " << inc_y << "\n";

		//if ( p_3[0] - inc_x != 0 || p_3[1] - inc_y != 0 )
			//correct( p_3, inc_x, inc_y );

		var_x =  rand( ) % 4 - 3;
		var_y =  rand( ) % 4 - 3;
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );
		std::cout << "correcting x by: " << p_3[0] - inc_x + var_x << " correcting y by: " << p_3[1] - inc_y + var_y << "\n";
		
		//std::cout << "correction lost_x: " << lost_x << "correction lost_y: " << lost_y << "\n";

		click( );

		move (var_x * -1, var_y * -1);

		sleep_t = ( rand() % 404 - 41 + t_seers[i] );
		//Sleep( sleep_t );
		Sleep( 1000 );

	}
	return;
}

void seers_box( int * laps, std::array< int, 2 > &start, std::array< int, 2 > &initial )
{
	double x = 0;
	double x_prev = 0;
	double y = 0;
	double y_prev = 0;
	double x_move;
	double y_move;
	int casted_x;
	int casted_y;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	std::array< int, 2> p_0 { };
	std::array< int, 2> p_3 { };
	std::array< int, 2> p_1 { };
	std::array< int, 2> p_2 { };
	std::array< int, 2 > current { };
	std::array< int, 2> var = { 0, 0 };

	srand( time( NULL ) );


	for ( int i = 0; i < 6; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { box_seers[i][0] - var[0], box_seers[i][1] - var[1] };

		if ( box_seers[i][2] == 0)
			var[0] = 0;
		else
			var[0] = rand( ) % box_seers[i][2] - box_seers[i][2];
		if ( box_seers[i][3] == 0)
			var[1] = 0;
		else
			var[1] = rand( ) % box_seers[i][3] - box_seers[i][3];

		if ( i == 3 )
			var[0] = rand ( ) % 30;

		p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
		p_1 = gen( p_3 );
		p_2 = gen( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		inc_x = 0;
		inc_y = 0;

		for (double t = 0; t < 1; t += 0.05)
		{
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			casted_x = int ( x_move );
			casted_y = int ( y_move );

			inc_x += casted_x;
			inc_y += casted_y;


			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 7 + 3;

			Sleep( sleep_t );
		}

		var_x =  rand( ) % 4 - 3;
		var_y =  rand( ) % 4 - 3;

		if ( i == 5 )
		{
			var_x = 0;
			var_y = 0;
			//std::cout << p_3[0] << " " << p_3[1] << " " << var[0] << " " << var[1] << " " << var_x << " " << var_y << "\n";
		}

		//std::cout << "x moved: " << inc_x << " y moved: " << inc_y << "\n";
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );
		//std::cout << "correcting x by: " << p_3[0] - inc_x + var_x << " correcting y by: " << p_3[1] - inc_y + var_y << "\n";

		//std::cout << "correction lost_x: " << lost_x << "correction lost_y: " << lost_y << "\n";

		if ( i != 5 )
			//click( );
			click2( var_x * -1, var_y * -1 );

		//move( var_x * -1, var_y * -1 );

		if (i == 5)
		{
			var_x = rand( ) % 3 + 1;
			var_y = rand( ) % 3 + 1;
			//move( var_x * -1, var_y * -1 );
			//move( -1, -1 );
			click2( var_x * -1, var_y * -1 );
			* laps = * laps + 1;
			std::cout << "laps completed: " << * laps << std::endl;
		}
			

		sleep_t = ( rand() % 87 + 11 + t_seers[i] );
		Sleep( sleep_t );

		if ( pressing( VK_RMENU ) ) {
			std::cout << "paused" << std::endl;

			while ( pressing( VK_RMENU ) )
				Sleep( 1 );
			while ( !pressing( VK_RMENU ) )
				Sleep( 1 );

			current = getpos( );
			start = { current[0], current[1] };
			initial = { current[0], current[1] };

			std::cout << "resuming" << std::endl;
			Sleep( 300 );
			return;
		}

		Sleep( 1 );

	}
	return;
}

void ardy( int * laps, std::array< int, 2 > &start, std::array< int, 2 > &initial )
{
	double x = 0;
	double x_prev = 0;
	double y = 0;
	double y_prev = 0;
	double x_move;
	double y_move;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	std::array< int, 2> p_0 { };
	std::array< int, 2> p_3 { };
	std::array< int, 2> p_1 { };
	std::array< int, 2> p_2 { };
	std::array< int, 2 > current { };
	std::array< int, 2> var = { 0, 0 };

	srand( time( NULL ) );


	for ( int i = 0; i < 7; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { box_ardy[i][0] - var[0], box_ardy[i][1] - var[1] };

		if ( box_ardy[i][2] == 0)
			var[0] = 0;
		else
			var[0] = rand( ) % box_ardy[i][2] - box_ardy[i][2];
		if ( box_ardy[i][3] == 0)
			var[1] = 0;
		else
			var[1] = rand( ) % box_ardy[i][3] - box_ardy[i][3];

		p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
		p_1 = gen( p_3 );
		p_2 = gen( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		inc_x = 0;
		inc_y = 0;

		if ( i == 1 )
			scroll( 120 );

		//if ( i == 3 )
			//send( );

		for (double t = 0; t < 1; t += 0.05)
		{
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			inc_x += int ( x_move );
			inc_y += int ( y_move );


			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 7 + 3;

			Sleep( sleep_t );
		}

		var_x =  rand( ) % 4 - 3;
		var_y =  rand( ) % 4 - 3;

		if ( i == 6 )
		{
			var_x = 0;
			var_y = 0;
			//std::cout << p_3[0] << " " << p_3[1] << " " << var[0] << " " << var[1] << " " << var_x << " " << var_y << "\n";
		}

		//std::cout << "x moved: " << inc_x << " y moved: " << inc_y << "\n";
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );
		//std::cout << "correcting x by: " << p_3[0] - inc_x + var_x << " correcting y by: " << p_3[1] - inc_y + var_y << "\n";

		//std::cout << "correction lost_x: " << lost_x << "correction lost_y: " << lost_y << "\n";

		if ( i != 6 )
			//click( );
			click2( var_x * -1, var_y * -1 );

		//move( var_x * -1, var_y * -1 );

		if (i == 6)
		{
			//var_x = rand( ) % 3 + 1;
			//var_y = rand( ) % 3 + 1;
			click2( var_x, var_y );
			* laps = * laps + 1;
			std::cout << "laps completed: " << * laps << std::endl;
		}


		sleep_t = ( rand() % 71 + 11 + t_ardy[i] );
		Sleep( sleep_t );

		if ( pressing( VK_RMENU ) ) {
			std::cout << "paused" << std::endl;

			while ( pressing( VK_RMENU ) )
				Sleep( 1 );
			while ( !pressing( VK_RMENU ) )
				Sleep( 1 );

			current = getpos( );
			start = { current[0], current[1] };
			initial = { current[0], current[1] };

			std::cout << "resuming" << std::endl;
			Sleep( 300 );
			return;
		}

		Sleep( 1 );

	}
	return;
}

void fish( )
{
	double x = 0;
	double x_prev = 0;
	double y = 0;
	double y_prev = 0;
	double x_move;
	double y_move;
	int casted_x;
	int casted_y;
	//double lost_x = 0;
	//double lost_y = 0;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	std::array< int, 2> p_0;
	std::array< int, 2> p_3;
	std::array< int, 2> p_1;
	std::array< int, 2> p_2;
	std::array< int, 2> var = { 0, 0 };
	int slept;

	srand( time( NULL ) );


	for ( int i = 0; i < 4; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { fishing[i][0] - var[0], fishing[i][1] - var[1] };

		if ( fishing[i][2] == 0)
			var[0] = 0;
		else
			//var[0] = rand( ) % fishing[i][2] - ( int ( fishing[i][2] * 0.5 ) );
			var[0] = rand( ) % fishing[i][2];
		if ( fishing[i][3] == 0)
			var[1] = 0;
		else
			//var[1] = rand( ) % fishing[i][3] - ( int ( fishing[i][3] * 0.5 ) );
			var[1] = rand( ) % fishing[i][3];

		p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
		p_1 = gen( p_3 );
		p_2 = gen( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		//lost_x = 0;
		//lost_y = 0;
		inc_x = 0;
		inc_y = 0;
		slept = 0;
		//std::cout << "i: " << i << "\n\n";

		for (double t = 0; t < 1; t += 0.1)
		{
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			casted_x = int ( x_move );
			casted_y = int ( y_move );
			//lost_x += ( x_move - casted_x );
			//lost_y += ( y_move - casted_y );
			inc_x += casted_x;
			inc_y += casted_y;

			//std::cout << x << " " << x_prev << " " << x_move << " " << casted_x << " " << lost_x << "\n";

			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 5 + 3;
			slept += sleep_t;

			Sleep( sleep_t );
		}

		//std::cout << "i: " << i << " " << box_seers[i][0] << " " << box_seers[i][1] << "\n";
		//std::cout << "moved x: " << inc_x << " moved y: " << inc_y << "\n";

		//if ( p_3[0] - inc_x != 0 || p_3[1] - inc_y != 0 )
		//correct( p_3, inc_x, inc_y );

		var_x =  rand( ) % 4 - 3;
		var_y =  rand( ) % 4 - 3;

		if ( i == 3 )
		{
			var_x = 0;
			var_y = 0;
			//std::cout << p_3[0] << " " << p_3[1] << " " << var[0] << " " << var[1] << " " << var_x << " " << var_y << "\n";
		}

		//std::cout << "x moved: " << inc_x << " y moved: " << inc_y << "\n";
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );
		//std::cout << "correcting x by: " << p_3[0] - inc_x + var_x << " correcting y by: " << p_3[1] - inc_y + var_y << "\n";

		//std::cout << "correction lost_x: " << lost_x << "correction lost_y: " << lost_y << "\n";

		if ( i != 3 )
			click( );

		move( var_x * -1, var_y * -1 );

		if (i == 3)
		{
			//var_x = rand( ) % 2;
			//var_y = rand( ) % 2;
			//move( var_x * -1, var_y * -1 );
			//move( -1, -1 );
			click( );
		}

		sleep_t = t_fishing[i] - slept;
		//sleep_t = ( rand() % 20 - 10 + t_fishing[i] );
		std::cout << "sleeping for: " << sleep_t << ", previously slept for: " << slept << std::endl;
		Sleep( sleep_t );

		if ( pressing( VK_F8 ) ) {
			std::cout << "paused, waiting for f9" << std::endl;
			while ( !pressing( VK_F9 ) )
				Sleep(1);
			std::cout << "restarting" << std::endl;
			return;
		}

		//Sleep( 1000 );

	}
	return;
}

void drop_inv( )
{
	double x;
	double x_prev;
	double y;
	double y_prev;
	double x_move;
	double y_move;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	int slept;
	std::array< int, 2> p_0 { };
	std::array< int, 2> p_3 { };
	std::array< int, 2> p_1 { };
	std::array< int, 2> p_2 { };
	std::array< int, 2> var = { 0, 0 };

	srand( time( NULL ) );

	while ( !pressing( VK_RMENU ) )
		Sleep(1);

	Sleep( rand( ) % 64 + 292 );

	click( );

	for ( int i = 0; i < 25; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { drop[i][0] - var[0], drop[i][1] - var[1] };

		if ( drop[i][2] == 0)
			var[0] = 0;
		else
			var[0] = rand( ) % drop[i][2] - 5;
			//var[0] = rand( ) % drop[i][2];
		if ( drop[i][3] == 0)
			var[1] = 0;
		else
			var[1] = rand( ) % drop[i][3] - 5;
			//var[1] = rand( ) % drop[i][3];

		p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
		p_1 = gen_small( p_3 );
		p_2 = gen_small( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		inc_x = 0;
		inc_y = 0;
		slept = 0;
		//std::cout << "i: " << i << "\n\n";

		for (double t = 0; t < 1; t += 0.1)
		{
			if ( i == 7 || i == 15 || i == 23)
				if ( t != 0 )
					t -= 0.05;
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			inc_x += int ( x_move );
			inc_y += int ( y_move );

			//std::cout << x << " " << x_prev << " " << x_move << " " << casted_x << " " << lost_x << "\n";

			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 6 + 2;
			slept += sleep_t;

			Sleep( sleep_t );
		}

		//std::cout << "i: " << i << " " << box_seers[i][0] << " " << box_seers[i][1] << "\n";
		//std::cout << "moved x: " << inc_x << " moved y: " << inc_y << "\n";

		//if ( p_3[0] - inc_x != 0 || p_3[1] - inc_y != 0 )
		//correct( p_3, inc_x, inc_y );

		var_x =  rand( ) % 3 - 1;
		var_y =  rand( ) % 3 - 1;

		if ( i == 3 )
		{
			var_x = 0;
			var_y = 0;
			//std::cout << p_3[0] << " " << p_3[1] << " " << var[0] << " " << var[1] << " " << var_x << " " << var_y << "\n";
		}

		//std::cout << "x moved: " << inc_x << " y moved: " << inc_y << "\n";
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );

		click2( var_x * -1, var_y * -1);

		//sleep_t = rand() % 60 + 53;
		//sleep_t = drop_sleep[i] - slept + rand( ) % 16 + 11;
		//sleep_t = rand( ) % 10 + 3;
		//std::cout << "sleeping for: " << sleep_t << std::endl;
		//Sleep( sleep_t );

		if ( pressing( VK_F8 ) ) {
			std::cout << "paused, waiting for f9" << std::endl;
			while ( !pressing( VK_F9 ) )
				Sleep(1);
			std::cout << "restarting" << std::endl;
			return;
		}

		//Sleep( 1000 );

	}

	Sleep( 10000 );
	return;
}

void glassmake( int * laps, std::array< int, 2 > &start, std::array< int, 2 > &initial )
{
	double x;
	double x_prev;
	double y;
	double y_prev;
	double x_move;
	double y_move;
	int sleep_t;
	int inc_x;
	int inc_y;
	int var_x = 0;
	int var_y = 0;
	int slept;
	std::array< int, 2> p_0 { };
	std::array< int, 2> p_3 { };
	std::array< int, 2> p_1 { };
	std::array< int, 2> p_2 { };
	std::array< int, 2 > current { };
	std::array< int, 2> var = { 0, 0 };

	srand( time( NULL ) );

	var_x =  rand( ) % 3 - 1;
	var_y =  rand( ) % 3 - 1;

	for ( int j = 0; j < 3; j++ )
	{
		click2( var_x * -1, var_y * -1 );
		Sleep( rand( ) % 521 + 420 );
		var_x = rand( ) % 3 - 1;
		var_y = rand( ) % 3 - 1;
	}

	for ( int i = 0; i < 5; i++ )
	{
		p_0 = { 0, 0 };
		p_3 = { superglass[i][0] - var[0], superglass[i][1] - var[1] };

		if ( superglass[i][2] == 0)
			var[0] = 0;
		else
			var[0] = rand( ) % superglass[i][2] - 5;
		//var[0] = rand( ) % drop[i][2];
		if ( superglass[i][3] == 0)
			var[1] = 0;
		else
			var[1] = rand( ) % superglass[i][3] - 5;
		//var[1] = rand( ) % drop[i][3];

		p_3 = { p_3[0] + var[0], p_3[1] + var[1] };
		p_1 = gen_small( p_3 );
		p_2 = gen_small( p_3 );

		x = 0;
		y = 0;
		x_prev = 0;
		y_prev = 0;
		inc_x = 0;
		inc_y = 0;
		slept = 0;

		if ( i == 1 )
			send_input( DIKEYBOARD_ESCAPE );

		for (double t = 0; t < 1; t += 0.1)
		{
			if ( i != 0 )
				if ( t != 0 )
					t -= 0.05;
			x_prev = x;
			y_prev = y;

			x = bezier( p_0[0], p_1[0], p_2[0], p_3[0], t );
			y = bezier( p_0[1], p_1[1], p_2[1], p_3[1], t );

			x_move = x - x_prev + 0.5;
			y_move = y - y_prev + 0.5;

			inc_x += int ( x_move );
			inc_y += int ( y_move );

			//std::cout << x << " " << x_prev << " " << x_move << " " << casted_x << " " << lost_x << "\n";

			move( int ( x_move ), int ( y_move ) );

			sleep_t = rand() % 6 + 2;
			slept += sleep_t;

			Sleep( sleep_t );
		}

		/* if ( i == 3 )
		{
			var_x = 0;
			var_y = 0;
			//std::cout << p_3[0] << " " << p_3[1] << " " << var[0] << " " << var[1] << " " << var_x << " " << var_y << "\n";
		}
		*/

		//std::cout << "x moved: " << inc_x << " y moved: " << inc_y << "\n";
		move( p_3[0] - inc_x + var_x, p_3[1] - inc_y + var_y );

		if ( i != 4 )
			click2( var_x * -1, var_y * -1 );

		if ( pressing( VK_RMENU ) ) {
			std::cout << "paused" << std::endl;

			while ( pressing( VK_RMENU ) )
				Sleep( 1 );
			while ( !pressing( VK_RMENU ) )
				Sleep( 1 );

			current = getpos( );
			start = { current[0], current[1] };
			initial = { current[0], current[1] };

			std::cout << "resuming" << std::endl;
			Sleep( 300 );
			return;
		}

		sleep_t = ( rand() % 86 + 173 + t_superglass[i] );
		
		if ( i != 4 )
			Sleep( sleep_t );
		else
			Sleep( rand( ) % 40 + 15 );
	}

	* laps = * laps + 1;

	return;
}
