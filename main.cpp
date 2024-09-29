#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class NimGame {
private:
    vector<int> piles;

    // 顯示目前的石堆狀況
    void printPiles() const {
        cout << "目前的石堆: ";
        for (int pile : piles) {
            cout << pile << " ";
        }
        cout << endl;
    }

    // 檢查遊戲是否結束
    bool isGameOver() const {
        for (int pile : piles) {
            if (pile != 0) return false;
        }
        return true;
    }

    // 玩家移動
    void playerMove() {
        int pileIndex, stones;
        while (true) {
            cout << "選擇一個石堆 (0-" << piles.size() - 1 << "): ";
            cin >> pileIndex;
            if (pileIndex < 0 || pileIndex >= piles.size() || piles[pileIndex] == 0) {
                cout << "無效的石堆，請重新選擇。" << endl;
                continue;
            }
            cout << "選擇要拿走的石頭數量 (1-" << piles[pileIndex] << "): ";
            cin >> stones;
            if (stones < 1 || stones > piles[pileIndex]) {
                cout << "無效的數量，請重新選擇。" << endl;
                continue;
            }
            piles[pileIndex] -= stones;
            break;
        }
    }

    // 電腦移動
    void computerMove() {
        int xorSum = 0;
        for (int pile : piles) {
            xorSum ^= pile;
        }

        if (xorSum == 0) {
            // 如果 XOR 和為 0，隨機選擇一個石堆並拿走一顆石頭
            for (int i = 0; i < piles.size(); ++i) {
                if (piles[i] > 0) {
                    piles[i]--;
                    break;
                }
            }
        } else {
            // 否則，找到最佳移動
            for (int i = 0; i < piles.size(); ++i) {
                int target = piles[i] ^ xorSum;
                if (target < piles[i]) {
                    piles[i] = target;
                    break;
                }
            }
        }
        cout << "電腦已經移動。" << endl;
    }

public:
    NimGame(int numPiles) {
        srand(time(0));
        piles.resize(numPiles);
        for (int& pile : piles) {
            pile = 1 + rand() % 10; // 每個石堆隨機有 1 到 10 顆石頭
        }
    }

    void play() {
        char firstMove;
        cout << "你想先移動嗎？ (y/n): ";
        cin >> firstMove;

        bool playerTurn = (firstMove == 'y');

        while (!isGameOver()) {
            printPiles();
            if (playerTurn) {
                playerMove();
            } else {
                computerMove();
            }
            playerTurn = !playerTurn;
        }

        if (playerTurn) {
            cout << "電腦贏了！" << endl;
        } else {
            cout << "你贏了！" << endl;
        }
    }
};

int main() {
    int numPiles = 3 + rand() % 3; // 隨機生成 3 到 5 個石堆
    NimGame game(numPiles);
    game.play();
    return 0;
}
