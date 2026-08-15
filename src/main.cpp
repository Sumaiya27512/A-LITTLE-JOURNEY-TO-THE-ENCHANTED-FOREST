#include <graphics.h>
#include <conio.h>

int main() {
    // গ্রাফিক্স উইন্ডো তৈরি
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // ==========================================
    // ১. স্টার্ট স্ক্রিন (START SCREEN)
    // ==========================================
    setbkcolor(LIGHTBLUE); // আকাশী ব্যাকগ্রাউন্ড
    cleardevice();

    // START বাটন তৈরি (সবুজ বক্স)
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(200, 150, 400, 230);

    // বাটনের ভেতরের লেখা
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(220, 180, (char*)"PRESS ENTER");

    getch(); // এন্টার বা যেকোনো কি চাপলে গল্প শুরু হবে

    // ==========================================
    // ২. গল্পের স্ক্রিন - দিন (STORY SCREEN - DAY)
    // ==========================================
    setbkcolor(LIGHTGREEN); // দিনের বনের ব্যাকগ্রাউন্ড
    cleardevice();

    // একটি সহজ গাছ আঁকা
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(100, 200, 130, 300); // গাছের গুঁড়ি
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(115, 170, 40, 40); // গাছের পাতা

    // আমাদের ক্যারেক্টার (একটি লাল বৃত্ত বা বল)
    int charX = 300; 
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(charX, 260, 25, 25);

    // ওপরের টেক্সট
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(50, 40, (char*)"Mitu is walking in the forest...");
    outtextxy(50, 70, (char*)"Press ANY KEY to see NIGHT!");

    getch(); // যেকোনো কি চাপলে রাত হবে

    // ==========================================
    // ৩. গল্পের স্ক্রিন - রাত (STORY SCREEN - NIGHT)
    // ==========================================
    setbkcolor(BLACK); // রাতের অন্ধকার ব্যাকগ্রাউন্ড
    cleardevice();

    // রাতের বেলা গাছের রঙ পরিবর্তন
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(100, 200, 130, 300);
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(115, 170, 40, 40);

    // রাতে ক্যারেক্টারটি আগের জায়গায় থাকবে
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(charX, 260, 25, 25);

    // চাঁদের আলো (ছোট একটি সাদা বৃত্ত)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(500, 70, 20, 20);

    // END বাটন তৈরি (লাল বক্স)
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(220, 320, 380, 370);

    setcolor(WHITE);
    outtextxy(240, 340, (char*)"PRESS TO END");

    getch(); // যেকোনো কি চাপলে প্রজেক্ট শেষ হবে

    // গ্রাফিক্স বন্ধ করা
    closegraph();
    return 0;
}
