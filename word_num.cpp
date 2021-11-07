#define _CRT_SECURE_NO_WARNINGS

#include <bangtal>
#include <cstdlib>
#include <ctime>

using namespace bangtal;

//짝수인지 아닌지 모음인지 아닌지를 판별하는 정보를 가진 오브젝트 클래스
class problem {
    bool even;
    bool collection;
    ObjectPtr num;
    ObjectPtr word;
public:
    problem() :even(false), collection(false){};
    problem(bool a, bool b, ObjectPtr c,ObjectPtr d) : even(a), collection(b), num(c), word(d){};
    void set(bool a, bool b, ObjectPtr c, ObjectPtr d) {
        even = a; collection = b;
        num = c;word = d;
    }
    void show() {
        num->show();
        word->show();
    }
    void hide() {
        num->hide();
        word->hide();
    }
    void locate(ScenePtr scene,int x, int y) {
        num->locate(scene, x, y);
        word->locate(scene, x + 120, y);
    }
    bool Is_even() { return even; }
    bool Is_collection() { return collection; }
};

int x[2] = { 190,615 };
int y[2] = { 130,440 };
bool Is_correct(int X, int Y, problem p) {
    if (X == x[0] && Y == y[1]) {
        if (p.Is_even()) return false;
        else return true;
    }
    else if (X == x[0] && Y == y[0]) {
        if (p.Is_even()) return true;
        else return false;
    }
    else if (X == x[1] && Y == y[0]) {
        if (p.Is_collection()) return true;
        else return false;
    }
    else {
        if (p.Is_collection()) return false;
        else return true;
    }
}

int main()
{
    bool tf[2] = { true,false };
    //문제 21개 생성
    ObjectPtr num;
    ObjectPtr word;
    srand(time(0));
    auto scene=Scene::create("", "Images/배경1.png");
    problem prob[21];
    char path[70];
    for (int i = 0;i < 21;i++) {
        bool bool1, bool2;
        bool1 = tf[rand() % 2];
        bool2 = tf[rand() % 2];
        int n1, n2;
        n1 = rand() % 14;
        n2 = rand() % 5;
        if (bool1) {
            sprintf(path, "Images/숫자%d.png", n2+5);
            num = Object::create(path, scene,0,0);
        }
        else {
            sprintf(path, "Images/숫자%d.png", n2 );
            num = Object::create(path, scene,0,0);
        }

        if (bool2) {
            sprintf(path, "Images/글자%d.png",n1 + 14);
            word = Object::create(path, scene,0,0);
        }
        else {
            sprintf(path, "Images/글자%d.png",n1);
            word = Object::create(path, scene,0,0);
        }
        num->setScale(0.8f);
        word->setScale(0.8f);
        prob[i].set(bool1, bool2, num, word);
        prob[i].hide();
    }
    printf("\n");
    auto right_button = Object::create("Images/같음.png", scene, 10, 50);
    auto wrong_button = Object::create("Images/다름.png", scene, 990, 50);

    int correct = 0, wrong = 0;
    int X, Y;
    int n, m,i=0;
    n = rand() % 2;
    m = rand() % 2;
    X = x[n];Y = y[m];
    prob[0].show();
    prob[0].locate(scene, X, Y);

    right_button->setOnMouseCallback([&](ObjectPtr object, int x1, int y1, MouseAction action)->bool{
        if (i < 20) {
            if (Is_correct(X, Y, prob[i])) {
                correct++;
                printf("%d : 0\n",i+1);
            }
            else {
                wrong++;
                printf("%d : 1\n",i+1);
            }
            prob[i].hide();
            i++;
            n = rand() % 2;
            m = rand() % 2;
            X = x[n];
            Y = y[m];
            prob[i].show();
            prob[i].locate(scene, X, Y);
            if (i == 20) {
                sprintf(path, "정답 : %d, 오답 : %d", correct, wrong);
                printf("correct : %d, wrong : %d\n", correct, wrong);
                showMessage(path);
            }
        }
        return true;
        });

    wrong_button->setOnMouseCallback([&](ObjectPtr object, int x1, int y1, MouseAction action)->bool {
        if (i < 20) {
            if (Is_correct(X, Y, prob[i])) {
                wrong++;
                printf("%d : 1\n",i+1);
            }
            else {
                correct++;
                printf("%d : 0\n",i+1);
            }
            prob[i].hide();
            i++;
            n = rand() % 2;
            m = rand() % 2;
            X = x[n];
            Y = y[m];
            prob[i].show();
            prob[i].locate(scene, X, Y);
            if (i == 20) {
                sprintf(path, "정답 : %d, 오답 : %d", correct, wrong);
                printf("correct : %d, wrong : %d\n", correct, wrong);
                showMessage(path);
            }
        }
        else
            return true;
        return true;
        });

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    startGame(scene);
}
