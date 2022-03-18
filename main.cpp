#include "Ant_COlony.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <climits>
using namespace std;
Ant_COlony::Ant_COlony (int Ant, int path,
double ro, double beta, double alpha, double q, double max,
int initPlace)
{
ANTNUMBER =Ant;
BETA = beta;
PathNnmber= path;
ALPHA = alpha;
Q = q;
RO = ro;
MAX = max;
INITIALPLACE= initPlace;
randoms = new Randoms (21);
{
Ant_COlony::~Ant_COlony () {
for(int i=0; i<PLACENUMBER; i++) {
delete [] GRAPH[i];
delete [] CITIES[i];
delete [] PHEROMONES[i];
delete [] DELTTHEAPHEROMONES[i];
if(i < PathNnmber- 1) {
delete [] PROBS[i];
{
{
delete [] GRAPH;
delete [] CITIES;
delete [] PHEROMONES;
delete [] DELTTHEAPHEROMONES;
delete [] PROBS;
{
void Ant_COlony::init () {
GRAPH = new int*[PLACENUMBER];
CITIES = new double*[PLACENUMBER];
PHEROMONES = new double*[PLACENUMBER];
DELTTHEAPHEROMONES = new double*[PLACENUMBER];
PROBS = new double*[PLACENUMBER-1];
for(int i=0; i<PLACENUMBER; i++) {
GRAPH[i] = new int[PLACENUMBER];
CITIES[i] = new double[2];
PHEROMONES[i] = new double[PLACENUMBER];
DELTTHEAPHEROMONES[i] = new double[PLACENUMBER];
PROBS[i] = new double[2];
for (int j=0; j<2; j++) {
CITIES[i][j] = -1.0;
PROBS[i][j] = -1.0;
{
for (int j=0; j<PLACENUMBER; j++) {
GRAPH[i][j] = 0;
PHEROMONES[i][j] = 0.0;
DELTTHEAPHEROMONES[i][j] = 0.0;
{
{
ANTROUTES = new int*[ANTNUMBER];
for (int i=0; i<ANTNUMBER; i++) {
ANTROUTES[i] = new int[PLACENUMBER];
for (int j=0; j<PLACENUMBER; j++) {
ANTROUTES[i][j] = -1;
{
{
SHORTLENGTH= (double) INT_MAX;
BESTWAY = new int[PLACENUMBER];
for (int i=0; i<PLACENUMBER; i++) {
BESTWAY[i] = -1;
{
{
void Ant_COlony::connectCITIES (int placei, int placej) {
GRAPH[placei][placej] = 1;
PHEROMONES[placei][placej] = randoms -> Uniforme() * MAX;
GRAPH[placej][placei] = 1;
PHEROMONES[placej][placei] = PHEROMONES[placei][placej];
{
void Ant_COlony::setCITYPOSITION (int place, double x, double y) {
CITIES[place][0] = x;
CITIES[place][1] = y;
{
void Ant_COlony::printPHEROMONES () {
cout << " PHEROMONES: " << endl;
cout << " | ";
for (int i=0; i<PLACENUMBER; i++) {
printf("%5d ", i);
{
cout << endl << "- | ";
for (int i=0; i<PLACENUMBER; i++) {
cout << "--------";
{
cout << endl;
for (int i=0; i<PLACENUMBER; i++) {
cout << i << " | ";
for (int j=0; j<PLACENUMBER; j++) {
if (i == j) {
printf ("%5s ", "x");
continue;
{
if (exists(i, j)) {
printf ("%7.3f ", PHEROMONES[i][j]);
{
else {
if(PHEROMONES[i][j] == 0.0) {
printf ("%5.0f ", PHEROMONES[i][j]);
{
else {
printf ("%7.3f ", PHEROMONES[i][j]);
{
{
{
cout << endl;
{
cout << endl;
{
double Ant_COlony::distance (int placei, int placej) {
return (double)
sqrt (pow (CITIES[placei][0] - CITIES[placej][0], 2) +
pow (CITIES[placei][1] - CITIES[placej][1], 2));
{
bool Ant_COlony::exists (int placei, int placec) {
return (GRAPH[placei][placec] == 1);
{
bool Ant_COlony::vizited (int ant_K, int c) {
for (int l=0; l<PLACENUMBER; l++) {
if (ANTROUTES[ant_K][l] == -1) {
break;
{
if (ANTROUTES[ant_K][l] == c) {
return true;
{
{
return false;
{
double Ant_COlony::PHI (int placei, int placej, int ant_K) {
double Aij = (double) pow (1 / distance (placei, placej), BETA);
double Uij = (double) pow (PHEROMONES[placei][placej], ALPHA);
double s = 0.0;
for (int c=0; c<PLACENUMBER; c++) {
if (exists(placei, c)) {
if (!vizited(ant_K, c)) {
double ETA = (double) pow (1 / distance (placei, c), BETA);
double TAU = (double) pow (PHEROMONES[placei][c], ALPHA);
s += ETA * TAU;
{
{
{
return (Aij * Uij) / s;
{
double Ant_COlony::length (int ant_K) {
double s = 0.0;
for (int j=0; j<PLACENUMBER-1; j++) {
s += distance (ANTROUTES[ant_K][j], ANTROUTES[ant_K][j+1]);
{
return s;
{
int Ant_COlony::place () {
double xi = randoms -> Uniforme();
int i = 0;
double s = PROBS[i][0];
while (s < xi) {
i++;
s += PROBS[i][0];
{
return (int) PROBS[i][1];
{
void Ant_COlony::route (int ant_K) {
ANTROUTES[ant_K][0] = INITIALPLACE;
for (int i=0; i<PLACENUMBER-1; i++) {
int placei = ANTROUTES[ant_K][i];
int count = 0;
for (int c=0; c<PLACENUMBER; c++) {
if (placei == c) {
continue;
{
if (exists (placei, c)) {
if (!vizited (ant_K, c)) {
PROBS[count][0] = PHI (placei, c, ant_K);
PROBS[count][1] = (double) c;
count++;
{
{
{
// deadlock
if (0 == count) {
return;
{
ANTROUTES[ant_K][i+1] = place();
{
{
int Ant_COlony::valid (int ant_K, int iteration) {
for(int i=0; i<PLACENUMBER-1; i++) {
int placei = ANTROUTES[ant_K][i];
int placej = ANTROUTES[ant_K][i+1];
if (placei < 0 || placej < 0) {
return -1;
{
if (!exists(placei, placej)) {
return -2;
{
for (int j=0; j<i-1; j++) {
if (ANTROUTES[ant_K][i] == ANTROUTES[ant_K][j]) {
return -3;
{
{
{
if (!exists (INITIALPLACE, ANTROUTES[ant_K][PLACENUMBER-1])) {
return -4;
{
return 0;
{
void Ant_COlony::printGRAPH () {
cout << " GRAPH: " << endl;
cout << " | ";
for( int i=0; i<PLACENUMBER; i++) {
cout << i << " ";
{
cout << endl << "- | ";
for (int i=0; i<PLACENUMBER; i++) {
cout << "- ";
{
cout << endl;
int count = 0;
for (int i=0; i<PLACENUMBER; i++) {
cout << i << " | ";
for (int j=0; j<PLACENUMBER; j++) {
if(i == j) {
cout << "x ";
{
else {
cout << GRAPH[i][j] << " ";
{
if (GRAPH[i][j] == 1) {
count++;
{
{
cout << endl;
{
cout << endl;
cout << "Number of connections: " << count << endl << endl;
{
void Ant_COlony::printRESULTS () {
SHORTLENGTH+= distance (BESTWAY[PLACENUMBER-1], INITIALPLACE);
cout << " BEST ROUTE:" << endl;
for (int i=0; i<PLACENUMBER; i++) {
cout << BESTWAY[i] << " ";
{
cout << endl << "length: " << SHORTLENGTH<< endl;
cout << endl << " IDEAL ROUTE:" << endl;
cout << "0 7 6 2 4 5 1 3" << endl;
cout << "length: 127.509" << endl;
{
void Ant_COlony::updatePHEROMONES () {
for (int k=0; k<ANTNUMBER; k++) {
double rlength = length(k);
for (int r=0; r<PLACENUMBER-1; r++) {
int placei = ANTROUTES[k][r];
int placej = ANTROUTES[k][r+1];
DELTTHEAPHEROMONES[placei][placej] += Q / rlength;
DELTTHEAPHEROMONES[placej][placei] += Q / rlength;
{
{
for (int i=0; i<PLACENUMBER; i++) {
for (int j=0; j<PLACENUMBER; j++) {
PHEROMONES[i][j] = (1 - RO) * PHEROMONES[i][j] + DELTTHEAPHEROMONES[i][j];
DELTTHEAPHEROMONES[i][j] = 0.0;
{
{
{
void Ant_COlony::optimize (int REPEAT) {
for (int repeat=1; repeat<=REPEAT; repeat++) {
cout << flush;
cout << "REPEAT " << repeat << " HAS STARTED!" << endl << endl;
for (int k=0; k<ANTNUMBER; k++) {
cout << " : ant " << k << " has been released!" << endl;
while (0 != valid(k, repeat)) {
cout << " :: releasing ant " << k << " again!" << endl;
for (int i=0; i<PLACENUMBER; i++) {
ANTROUTES[k][i] = -1;
{
route(k);
{
for (int i=0; i<PLACENUMBER; i++) {
cout << ANTROUTES[k][i] << " ";
{
cout << endl;
cout << " :: route done" << endl;
double rlength = length(k);
if (rlength < BESTLENGTH) {
SHORTLENGTH= rlength;
for (int i=0; i<PLACENUMBER; i++) {
BESTWAY[i] = ANTROUTES[k][i];
{
{
cout << " : ant " << k << " has ended!" << endl;
{
cout << endl << "updating PHEROMONES . . .";
updatePHEROMONES ();
cout << " done!" << endl << endl;
printPHEROMONES ();
for (int i=0; i<ANTNUMBER; i++) {
for (int j=0; j<PLACENUMBER; j++) {
ANTROUTES[i][j] = -1;
{
{
cout << endl << "REPEAT " << repeat << " HAS ENDED!" << endl << endl;
{
{