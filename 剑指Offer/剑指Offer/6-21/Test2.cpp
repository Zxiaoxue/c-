/*************************************************************************
	> File Name: Test2.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Wed 21 Jun 2017 05:02:49 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
          if(pre == NULL || vin == NULL)
            return NULL;
        if(pre.size() != vin.size()){
            return NULL;
        } 
        if(startpre > endpre || startvin > endvin){
            return NULL;
        }
        TreeNode* root = _reConstructBinaryTree(pre, 0, pre.length, vin, 0,vin.length);
        return root;
    }
    
    TreeNode* _reConstructBinaryTree(vector<int> pre, int startpre,int endpre,vector<int>vin,int startvin,int endvin){
     
        TreeNode* root = new TreeNode(pre[startpre]);
        
        for(int i = startvin; i<endvin; i++){
            if(vin[i] == pre[startpre]){
                root->left = _reConstructBinaryTree(pre, startpre+1, startpre+i-startvin, vin, startvin, i-1);
                root->right = _reConstructBinaryTree(pre, startpre+i-startvin+1, endpre, vin, i+1, endvin);
            }
        }
        return root;
    }
};
