class AqiScale
{
public:
    AqiScale();
    char* getAQI(int pm25);
private:
    char iqa1[4] = "Bon";
    char iqa2[11] = "Acceptable";
    char iqa3[8] = "Mauvais";
    int meanIQA = 35;
    int goodpm25Limit = 25;
    int okpm25Limit = 50;
};