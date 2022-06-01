#include <iostream>
#include <vector>

using namespace std;

int main() {
  int m, n;
  cout << "Enter the number of processes: ";
  cin >> n;

  cout << endl << "Enter the number of resources: ";
  cin >> m;
  cout << endl;
  int alloc[n][m], finish[n], max_required[n][m], avail[m];
  int require[n], avail_req[m];

  vector < int > answer, answer_req;

  for (int i = 0; i < n; i++) {
    cout << "Process P" << i + 1 << ":" << endl;
    for (int j = 0; j < m; j++) {
      cout << "Enter max required instances of resource R" << j + 1 << ":";
      cin >> max_required[i][j];
    }
    cout << endl;
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << "Process P" << i + 1 << ":" << endl;
    for (int j = 0; j < m; j++) {
      cout << "Enter allocated instances of resource R" << j + 1 << ":";
      cin >> alloc[i][j];
    }
    cout << endl;
  }
  cout << endl;
  for (int i = 0; i < m; i++) {
    cout << "Enter instances of available resource" << i + 1 << ": ";
    cin >> avail[i];
    avail_req[i] = avail[i];
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    finish[i] = 0;
    require[i] = 0;
  }
  int need[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max_required[i][j] - alloc[i][j];
    }
  }
  bool no_safe_sequence = false;
  int current_pos = 0, start = 0;
  while (1) {
    bool check = true;
    for (int i = 0; i < n; i++) {
      if (finish[i] == 0) {
        check = false;
        break;
      }
    }
    if (check) {
      break;
    }
    bool found = false;
    do {
      bool applicable = true;
      for (int i = 0; i < m; i++) {
        if (need[current_pos][i] > avail[i]) {
          applicable = false;
          break;
        }
      }
      if (finish[current_pos] == 1) {
        applicable = false;
      }
      if (applicable) {
        answer.push_back(current_pos + 1);
        found = true;
        for (int i = 0; i < m; i++) {
          avail[i] += alloc[current_pos][i];
        }
        finish[current_pos] = 1;
        start = current_pos;
        break;
      }
      current_pos = (current_pos + 1) % n;
    } while (current_pos != start);
    if (!found) {
      no_safe_sequence = true;
      break;
    }
  }
  if (!no_safe_sequence) {
    cout << "SAFE SEQUENCE: ";
    for (int i = 0; i < answer.size(); i++) {
      cout << " P" << answer_req[i] << " ->";
      }
      cout << " END";
  } else {
    cout << "------ No Safe Sequence exists -----";
    cout << endl << "No request Granted Further!";
    return 0;
  }
  cout << endl;
  int process_id_request;
  cout << endl << "Enter the Process No. which wants to request for resources:";
  cin >> process_id_request;
  process_id_request--;
  int process_req_res[m];
  bool pre_condition = true;
  for (int i = 0; i < m; i++) {
    cout << "Enter the required instances of resource" << i + 1 << " : ";
    cin >> process_req_res[i];
    if (process_req_res[i] > avail_req[i]) {
      pre_condition = false;
      break;
    } else {
      avail_req[i] -= process_req_res[i];
    }
  }
  if (!pre_condition) {
    cout << "Request cannot be granted to the process!";
  } else {
    for (int i = 0; i < m; i++) {
      alloc[process_id_request][i] += process_req_res[i];
      need[process_id_request][i] -= process_req_res[i];
    }
    bool no_safe_sequence = false;
    int current_pos = 0, start = 0;
    while (1) {
      bool check = true;
      for (int i = 0; i < n; i++) {
        if (require[i] == 0) {
          check = false;
          break;
        }
      }
      if (check) {
        break;
      }
      bool found = false;
      do {
        bool applicable = true;
        for (int i = 0; i < m; i++) {
          if (need[current_pos][i] > avail_req[i]) {
            applicable = false;
            break;
          }
        }
        if (require[current_pos] == 1) {
          applicable = false;
        }
        if (applicable) {
          answer_req.push_back(current_pos + 1);
          found = true;
          for (int i = 0; i < m; i++) {
            avail_req[i] += alloc[current_pos][i];
          }
          require[current_pos] = 1;
          start = current_pos;
          break;
        }
        current_pos = (current_pos + 1) % n;
      } while (current_pos != start);
      if (!found) {
        no_safe_sequence = true;
        break;
      }
    }
    cout << endl;
    if (!no_safe_sequence) {
      cout << "SAFE SEQUENCE: ";
      for (int i = 0; i < answer_req.size(); i++) {
        cout << " P" << answer_req[i] << " ->";
      }
      cout << " END";
      cout << endl << endl << "As Safe Sequence exists, request will be granted to the process.";
    } else {
      cout << "NO SAFE SEQUENCE EXISTS!";
      cout << endl << "Hence, request will not be granted to the process.";
    }
  }
}