
class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};

        auto toDays = [&](string date) {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));

            for (int i = 0; i < month - 1; i++) {
                day += daysInMonth[i];
            }

            return day;
        };

        int startAlice = toDays(arriveAlice);
        int endAlice = toDays(leaveAlice);
        int startBob = toDays(arriveBob);
        int endBob = toDays(leaveBob);

        int start = max(startAlice, startBob);
        int end = min(endAlice, endBob);

        return max(0, end - start + 1);
    }
};
