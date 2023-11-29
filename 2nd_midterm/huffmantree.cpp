#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Node structure for the Huffman tree
struct Node {
    char data;
    unsigned freq;
    Node* left, * right;

    Node(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparison struct to be used for the priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(const string& data) {
    // Create a frequency table
    unordered_map<char, unsigned> freqTable;
    for (char el : data) {
        freqTable[el]++;
    }

    // Create a priority queue of Nodes
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (const auto& pair : freqTable) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* internalNode = new Node('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Function to generate Huffman codes
void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root) {
        if (root->data != '$') {
            huffmanCodes[root->data] = code;
        }

        generateHuffmanCodes(root->left, code + "0", huffmanCodes);
        generateHuffmanCodes(root->right, code + "1", huffmanCodes);
    }
}

// Function to encode data using Huffman codes
string huffmanEncode(const string& data, unordered_map<char, string>& huffmanCodes) {
    string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes[ch];
    }
    return encodedData;
}

// Function to decode data using Huffman tree
string huffmanDecode(const string& encodedData, Node* root) {
    string decodedData;
    Node* current = root;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->data != '$') {
            decodedData += current->data;
            current = root;
        }
    }
    return decodedData;
}

int main() {
    string data = "banana tree";

    // Build Huffman tree
    Node* huffmanTree = buildHuffmanTree(data);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    // Output results
    cout << "Character Codes:" << endl;
    for (const auto& pair : huffmanCodes) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }

    // Encode data
    string encodedData = huffmanEncode(data, huffmanCodes);

    // Decode data
    string decodedData = huffmanDecode(encodedData, huffmanTree);

    // Output results
    cout << "\nOriginal data: " << data << endl;
    cout << "Encoded data: " << encodedData << endl;
    cout << "Decoded data: " << decodedData << endl;

    // Clean up
    delete huffmanTree;

    return 0;
}

