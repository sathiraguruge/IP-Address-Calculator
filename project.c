#include <stdio.h>
#include <math.h>

int binConverter ( int no );
void creatingBarrays ( int barr1[], int barr2[], int barr3[], int barr4[], int bno1, int bno2, int bno3, int bno4 );
void creatingPrefixArr ( int prefixArr[], int prefix );
void creatingMergedArray ( int mergedArr[], int barr1[], int barr2[], int barr3[], int barr4[] );
void addingArrays ( int mergedArr[], int prefixArr [], int resultArr[] );
void netIdcal ( int resultArr[], int prefix );
void subnetCal ( int prefixArr[], int prefix );
void calBrod ( int mergedArr[], int prefix );
void lastCal ( int brod1, int brod2, int brod3, int brod4 );
void firstIp ( int mergedArr[], int prefix );
void classCal ( int prefix );
void hostsCal ( int prefix );
void wildCal ( int mergedArr[], int prefix );
int main ( void )
{
        int no1, no2, no3, no4, bno1, bno2, bno3, bno4, count, i, j, prefix;

	int barr1[8] = {0}, barr2[8] = {0}, barr3[8] = {0}, barr4[8] = {0};

	int prefixArr [ 32 ] = { 0 }, mergedArr [ 32 ], resultArr [ 32 ];

        printf ( "Enter IP Address:");
        scanf ( "%3d.%3d.%3d.%3d/%2d", &no1, &no2, &no3, &no4, &prefix );

	if ( ( no1 > 255 ) || ( no2 > 255 ) || ( no3 > 255 ) || ( no4 > 255 ) )
	{
		printf ( "Inalid IP address!\n");
		return 0;
	}
	puts("");

	printf ( "IP Address = %d.%d.%d.%d/%d\n", no1, no2, no3, no4, prefix );
	classCal ( prefix );
	creatingPrefixArr ( prefixArr, prefix );
        bno1 = binConverter ( no1 );
	bno2 = binConverter ( no2 );
	bno3 = binConverter ( no3 );
	bno4 = binConverter ( no4 );
	creatingBarrays ( barr1, barr2, barr3, barr4, bno1, bno2, bno3, bno4 );
	creatingMergedArray ( mergedArr, barr1, barr2, barr3, barr4 );
	addingArrays ( mergedArr, prefixArr, resultArr );
	netIdcal ( resultArr, prefix );
	wildCal ( mergedArr, prefix );
	subnetCal ( prefixArr, prefix );
	firstIp ( mergedArr, prefix );
	calBrod ( mergedArr, prefix );
	hostsCal ( prefix );
	puts("");
        return 0;
}

int binConverter ( int no )
{
        int powArray[] = { 128, 64, 32, 16, 8, 4, 2, 1 };

        int binArray[8];

        int count;

        for ( count = 0 ; count < 8 ; ++count )
        {
                if ( no < powArray [ count ] )
                {
                        binArray[ count ] = 0;
                }
                else
                {
                        binArray [ count ] = 1;
                        no -= powArray [ count ] ;
                }
        }

	int binNo = 0; 
	int i = 10000000;

	for ( count = 0 ; count < 8 ; ++count )
	{

		binNo += binArray [ count ] * i;
		i = i / 10;
	}
	return binNo;

}

void creatingBarrays ( int barr1[], int barr2[], int barr3[], int barr4[], int bno1, int bno2, int bno3, int bno4 )
{
	int i, j, count;

        i = 10, j = 1;

        for ( count = 7 ; count > -1 ; --count )
        {
                barr1[count] = ( bno1 % i ) / j;
                barr2[count] = ( bno2 % i ) / j;
                barr3[count] = ( bno3 % i ) / j;
                barr4[count] = ( bno4 % i ) / j;
                i = i*10;
                j = j*10;
        }
}

void creatingPrefixArr ( int prefixArr[], int prefix )
{
	int count;

        for ( count = 0 ; count < 32 ; ++count )
        {
                if ( count == prefix )
                        break;

                prefixArr [ count ] = 1;
        }

}

void creatingMergedArray ( int mergedArr[], int barr1[], int barr2[], int barr3[], int barr4[] )
{


        int count2 = 0, count;
        for ( count = 0 ; count < 8 ; ++count )
        {
                mergedArr [ count ] = barr1 [ count2 ];
                ++count2;
        }

        count2 = 0;
        for ( count = 8 ; count < 16 ; ++count )
        {
                mergedArr [ count ] = barr2 [ count2 ];
                ++count2;
        }

        count2 = 0;
        for ( count = 16 ; count < 24 ; ++count )
        {
                mergedArr [ count ] = barr3 [ count2 ];
                ++count2;
        }

        count2 = 0;
        for ( count = 24 ; count < 32 ; ++count )
        {
                mergedArr [ count ] = barr4 [ count2 ];
                ++count2;
        }
	
}

void addingArrays ( int mergedArr[], int prefixArr [], int resultArr[] )
{
	int count;

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( (  mergedArr [ count ] == 1 ) && ( prefixArr [ count ] == 1 ) )
		{
			resultArr [ count ] = 1;
		}
		else
			resultArr [ count ] = 0;
	}
}

void netIdcal ( int resultArr[], int prefix )
{

	int netArr[prefix];
	int count, i;
	int netId1= 0, netId2 = 0, netId3 = 0, netId4 = 0;
	
	for ( count = 0 ; count < prefix ; ++count )
	{
		netArr [ count ] = resultArr [ count ];
	}

	for ( count = 0 ; count < prefix ; ++count )
	{
		if ( ( count == 0 )|| ( count == 8 ) || ( count == 16 ) || ( count == 24 ) )
			i = 7;


		if ( count <  8 )			
			netId1 += netArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 16 )
			netId2 += netArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 24 )
			netId3 += netArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 32 )
			netId4 += netArr [ count ] * ( pow ( 2, i ) );
		--i;	
	}

	printf ( "Netword Address = %d.%d.%d.%d\n", netId1, netId2, netId3, netId4 );

	printf ( "Network ID = ");
	for ( count = 1 ; count <= 4 ; ++count )
	{
		if ( count == 1 )
			printf ( "%d", netId1 );

		if ( ( count == 2 ) && ( netId2 != 0 ) )
			printf ( ".%d", netId2 );

		if ( ( count == 3 ) && ( netId3 != 0 ) )
			printf ( ".%d", netId3 );
		
		if ( ( count == 4 ) && ( netId4 != 0 ) ) 
			printf ( ".%d", netId4 );
	}
	puts("");

}

void subnetCal ( int prefixArr[], int prefix )
{
	int subnetArr [ prefix ];
	int count, i;
	int sub1 = 0, sub2= 0, sub3 = 0, sub4= 0;	

	for ( count = 0 ; count < prefix ; ++count )
	{
		subnetArr [ count ] = prefixArr [ count ];
	}

	for ( count = 0 ; count < prefix ; ++count )
	{
		if ( ( count == 0 )|| ( count == 8 ) || ( count == 16 ) || ( count == 24 ) )
			i = 7;


		if ( count <  8 )			
			sub1 += subnetArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 16 )
			sub2 += subnetArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 24 )
			sub3 += subnetArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 32 )
			sub4 += subnetArr [ count ] * ( pow ( 2, i ) );
		--i;	
	}

        printf ( "Subnet Mask = %d.%d.%d.%d\n", sub1, sub2, sub3, sub4 );
}

void calBrod ( int mergedArr[], int prefix )
{
	int count, i, brod1 = 0, brod2 = 0, brod3 = 0, brod4 = 0;
	int broadArr [32];

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( count < prefix )
			broadArr [ count ] = mergedArr [ count ];	
		else
			broadArr [ count ] = 1;
	}

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( ( count == 0 )|| ( count == 8 ) || ( count == 16 ) || ( count == 24 ) )
			i = 7;


		if ( count <  8 )			
			brod1 += broadArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 16 )
			brod2 += broadArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 24 )
			brod3 += broadArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 32 )
			brod4 += broadArr [ count ] * ( pow ( 2, i ) );
		--i;	
	}

	lastCal ( brod1, brod2, brod3, brod4 );
	printf ( "Broadcast Address = %d.%d.%d.%d\n", brod1, brod2, brod3, brod4 );
}

void lastCal ( int brod1, int brod2, int brod3, int brod4 )
{
	int last = brod4 - 1;

	printf ( "Last Usable IP Address = %d.%d.%d.%d\n", brod1, brod2, brod3, last );
}

void firstIp ( int mergedArr[], int prefix )
{
	int count, i, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
	int firstArr [32];

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( count < prefix )
			firstArr [ count ] = mergedArr [ count ];	
		else
			firstArr [ count ] = 0;
	}

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( ( count == 0 )|| ( count == 8 ) || ( count == 16 ) || ( count == 24 ) )
			i = 7;

		if ( count <  8 )			
			f1 += firstArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 16 )
			f2 += firstArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 24 )
			f3 += firstArr [ count ] * ( pow ( 2, i ) );
		else if ( count < 32 )
			f4 += firstArr [ count ] * ( pow ( 2, i ) );
		--i;	
	}

	printf ( "First Usable IP Address = %d.%d.%d.%d\n", f1, f2, f3, f4 + 1 );
}

void classCal ( int prefix )
{
	if ( prefix == 8 )
		printf ( "Class = A\n" );
	else if ( prefix == 16 )
		printf ( "Class = B\n" );
	else if ( prefix == 24 )
		printf ( "Class = C\n" );
	else
		printf ( "Class = Classless\n" );
}

void hostsCal ( int prefix )
{

	int hostCount = pow ( 2,( 32 - prefix ) ) - 2;
	
	printf ( "Total Hosts/Networks = %d\n", hostCount );
}

void wildCal ( int mergedArr[], int prefix )
{

	int wildArr [ 32 ] ;
	int count, i;
	int w1 = 0, w2 = 0, w3 = 0, w4 = 0;

	for ( count = 0 ; count < 32 ; ++count )
	{
		if ( count < prefix )
			wildArr [ count ] = 0;
		else 
			wildArr [ count ] = 1;
	}

	for ( count = 0 ; count < 32 ; ++count )
        {
                if ( ( count == 0 )|| ( count == 8 ) || ( count == 16 ) || ( count == 24 ) )
                        i = 7;

                if ( count <  8 )
                        w1 += wildArr [ count ] * ( pow ( 2, i ) );
                else if ( count < 16 )
                        w2 += wildArr [ count ] * ( pow ( 2, i ) );
                else if ( count < 24 )
                        w3 += wildArr [ count ] * ( pow ( 2, i ) );
                else if ( count < 32 )
                        w4 += wildArr [ count ] * ( pow ( 2, i ) );
                --i;
        }

	printf ( "Wildcard = %d.%d.%d.%d\n", w1, w2, w3, w4 );
}
