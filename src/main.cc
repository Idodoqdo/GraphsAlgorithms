#include "menu.h"

int main() {
  Menu menu;
  int variant;  // выбранный пункт меню
  do {
    menu.PrintMenu();  // выводим меню на экран
    variant = menu.GetVariant(7);  // получаем номер выбранного пункта меню
    switch (variant) {
      case 1:
        menu.LoadGraphFromFile();
        break;
      case 2:
        menu.BreadthFirstSearch();
        break;
      case 3:
        menu.DepthFirstSearch();
        break;
      case 4:
        menu.ShortestPathBetweenTwoVertices();
        break;
      case 5:
        menu.ShortestPathsBetweenAllVertices();
        break;
      case 6:
        menu.LeastSpanningTree();
        break;
      case 7:
        menu.SolveTravelingSalesmanProblem();
        break;
    }
    if (variant != 9)
      system("pause");  // задерживаем выполнение, чтобы пользователь мог
                        // увидеть результат выполнения выбранного пункта
  } while (variant != 9);
  return 0;
}
