#include <bits/stdc++.h>
using namespace std;

// 벡터를 문자열 key로 변환 (문자 개수를 안전하게 표현)
string vectorKey(const vector<int>& vec) {
    string key;
    for (int v : vec) {
        key += to_string(v) + ",";
    }
    return key;
}

string findLongestAnagramSubstring(const string& A, const string& B) {
    int n = A.size();

    // 긴 길이부터 내려가며 탐색
    for (int len = n; len >= 1; --len) {
        unordered_set<string> b_freq_set;
        vector<int> freq(26, 0);

        // B에서 길이 len인 첫 윈도우
        for (int i = 0; i < len; ++i) {
            freq[B[i] - 'a']++;
        }
        b_freq_set.insert(vectorKey(freq));

        // 슬라이딩 윈도우로 B 전체 탐색
        for (int i = len; i < n; ++i) {
            freq[B[i - len] - 'a']--;
            freq[B[i] - 'a']++;
            b_freq_set.insert(vectorKey(freq));
        }

        // A에서 길이 len인 substring을 슬라이딩하며 비교
        vector<int> freqA(26, 0);
        for (int i = 0; i < len; ++i) {
            freqA[A[i] - 'a']++;
        }
        if (b_freq_set.count(vectorKey(freqA))) {
            return A.substr(0, len);
        }

        for (int i = len; i < n; ++i) {
            freqA[A[i - len] - 'a']--;
            freqA[A[i] - 'a']++;
            if (b_freq_set.count(vectorKey(freqA))) {
                return A.substr(i - len + 1, len);
            }
        }
    }

    return "NONE";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string A, B;
        cin >> A >> B;
        cout << findLongestAnagramSubstring(A, B) << '\n';
    }

    return 0;
}