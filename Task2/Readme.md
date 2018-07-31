# Bài tập lập trình 2: Tô màu đồ thị

## Đề bài
Bạn đã biết trong bài giảng:

**Mệnh đề** : Cho G là đồ thị với mọi đỉnh đều có bậc ≤ k. Nếu G liên thông và không chính quy, vậy thì χ(G) ≤ k.

 Chứng minh của mệnh đề này cho chúng ta cách xây dựng thứ tự các đỉnh để thuật toán tham lam tô màu đỉnh dùng không quá k màu cho đồ thị không chính quy. Bài tập này yêu cầu bạn cài đặt thuật toán này.

 **Nhiệm vụ**: Nhập đồ thị từ bàn phím dưới dạng danh sách cạnh. Đưa ra màn hình một cách tô màu đồ thị dùng

* không nhiều hơn k màu nếu G liên thông và không chính quy;
* không nhiều hơn k+1 màu nếu G không liên thông hoặc là chính quy.

**Dữ liệu vào**: từ file dothi.txt trong đó

* Dòng đầu tiên ghi hai số nguyên n và m là số đỉnh và số cạnh của đồ thị; 
* Ở m dòng tiếp theo, mỗi dòng ghi 2 số nguyên tương ứng với một cạnh của đồ thị.

**Dữ liệu ra**: file dothitomau.dot biểu diễn đồ thị ở dạng ngôn ngữ DOT với các đỉnh đã được tô màu.

## Ví dụ :
| Dữ liệu vào dothi.txt | Dữ liệu ra dothitomau.dot |
|---|---|
|5 5<br>1 2<br>2 3<br>3 4<br>4 1<br>1 5<br><br><br><br><br><br><br><br> | graph dothi<br>{<br>     5 [fillcolor=red, style=filled];<br>     4 [fillcolor=red, style=filled];<br>     1 [fillcolor=green, style=filled];<br>     3 [fillcolor=green, style=filled];<br>     2 [fillcolor=red, style=filled];<br>     1 -- 2;<br>     2 --3;<br>     3 -- 4;<br>     4 -- 1;<br>     1 --5;<br>} |

## Chạy chương trình
### Compile
`g++ coloring.cpp -o coloring`

`g++ randomgraph.cpp -o randomgraph`

### Run

`./randomgraph && ./coloring && dot -Tpdf dothitomau.dot -o graph.pdf`