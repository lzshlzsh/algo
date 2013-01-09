/*file artilleryPosition.cpp*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

class ArtilleryPosition
{
    private:
        int m_legalStates[60];
        int m_legalStatesNum;
        int m_m, m_n;
        char m_map[100][10];
        int m_artilleryNum;
        int m_dp[60][60][100];
   
        char m_inputFileName[100];
   
    private:
        bool getInfo(){
            std::ifstream input(m_inputFileName);
            /*input.open(m_inputFileName, std::ios::in);*/
            input>>m_n;/*get colum numbers*/
            input>>m_m;/*get line numbers*/
            /*colum numbers - legality test*/
            if (m_m < 0 || m_m > 10)
                return false;
            /*line numbers test*/
            if (m_n < 0 || m_n > 100)
                return false;
            /*get map*/
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++){
                    input>>m_map[i][j];
                }
            return true;
        }
    inline bool ok(int s){
        if (s < 0 || s >= m_m)
            return false;
        return true;
    }
    void calLegalStates(){
        int all_states = 1 << m_m;/*total states are 2^m, because each pos have two choices*/
/*         int max_states[1 << 10];  */
        for (int i = 0; i < all_states; i++){
            int flg = 1;
            /*if state i is illegal, delete it*/
            for (int j = 0; j < m_m; j++){
                /*pos j has an artllery*/
                if (i & (1 << j)){
                    /*illegal pos of artllery*/
                    if (
                        (ok(j - 2) && (i & (1 << (j - 2))))/*given state i, pos j-2 has an artllery*/
                        || (ok(j - 1) && (i & (1 << (j - 1))))/*pos j-1*/
                        || (ok(j + 1) && (i & (1 << (j + 1))))/*pos j+1*/
                        || (ok(j + 2) && (i & (1 << (j + 2))))/*pos j+2*/
                        ){
                            flg = 0;
                            break;
                        }
                }
            }
            /*incre legal states counter*/
            if (flg)
                m_legalStates[m_legalStatesNum++] = i;
        }
/*         memcpy(m_legalStates, max_states, m_legalStatesNum * sizeof(int));  */
    }
   
    int getMaxArtillery(int now, int last, int n){
        /*we should make sure that the artllery arrangement of current line - m_legalStates[now]
        and that of the above line - m_legalStates[last], if exists, are both legal*/
        int nb = 0;
        /*get artllery numbers of current line*/
        if (-1 != m_dp[now][last][n])
            return m_dp[now][last][n];
        nb = getArtsOfSingleLine(n, now);
        /*end condition of recurrence*/
        if (0 == n){
            m_dp[now][last][n] = nb;
            return nb;
        }
        if (1 == n){
            nb += getArtsOfSingleLine(n - 1, last);
            m_dp[now][last][n] = nb;
            return nb;
        }
        int haveArtillery = m_legalStates[now] | m_legalStates[last];
        int max = 0;
        for (int i = 0; i < m_legalStatesNum; i++){
            /*put artllery on mountain - illegal*/
            /*conflict*/
            if (!singleLineStateTest(n - 2, i) || (haveArtillery & m_legalStates[i]))
                continue;
            int max1 = getMaxArtillery(last, i, n - 1);
            max = max < max1 ? max1 : max;
        }
        m_dp[now][last][n] = max + nb;
        return max + nb;       
    }
   
    inline bool singleLineStateTest(int line, int s){
        /*if the pos is a mountain, and we put an artllery on it, that is
        illegal*/
        for (int i = 0; i < m_m; i++)
         if ('H' == m_map[line][i] && (m_legalStates[s] & (1 << i)))
            return false;
        return true;
    }
    int getArtsOfSingleLine(int line, int s){
        /*we should assure state s for line line is legal,
        we get artillerys of this line*/
        int nb = 0;
        for (int i = 0; i < m_m; i++)
            if (m_legalStates[s] & (1 << i))
            nb++;
        return nb;
    }
    public:
        ArtilleryPosition():m_legalStatesNum(0), m_m(0),
    m_n(0), m_artilleryNum(0){
        sprintf(m_inputFileName, "artilleryInput");
        memset(m_dp, 0xff, 60 * 60 * 100 * sizeof(int));
    }
    ArtilleryPosition(char *name):m_legalStatesNum(0), m_m(0),
    m_n(0), m_artilleryNum(0){
        snprintf(m_inputFileName, 100, "%s", name);
        memset(m_dp, 0xff, 60 * 60 * 100 * sizeof(int));
    }
    ~ArtilleryPosition(){}
   
    void Solve(){
        if (!this->getInfo())
            return;
        this->calLegalStates();
        if (!m_n)
            return;
        if (1 == m_n){
            /*just one line, easy to get the answer*/
            for (int i = 0; i < m_legalStatesNum; i++){
                int max = 0;
                if (singleLineStateTest(0, i)){
                    max = getArtsOfSingleLine(0, i);
                    m_artilleryNum = m_artilleryNum < max ? max : m_artilleryNum;
                }
            }
            return;
        }
        /*consider line n-1 and n-2*/
        for (int i = 0; i < m_legalStatesNum; i++)
        {
            if (!singleLineStateTest(m_n - 1, i))
                continue;
            for (int j = 0; j < m_legalStatesNum; j++){
                /*we put an artllery on the mountain of line n - 2
                or we put two artillerys on both line n-1 and line n-2 at
                the same colum*/
                if (!singleLineStateTest(m_n - 2, j) || (m_legalStates[i] & m_legalStates[j]))
                    continue;
                int max = getMaxArtillery(i, j, m_n - 1);
                m_artilleryNum = m_artilleryNum < max ? max : m_artilleryNum;
            }
        }
    }
    int GetMaxArtillery(){
        return m_artilleryNum;           
    }
   
   
};

int main()
{
    ArtilleryPosition ap;
    ap.Solve();
    std::cout<<ap.GetMaxArtillery()<<std::endl;
    return 0;
}
