#include <windows.h>
#include <math.h>
#include <vector>
#include <iostream>

const float PI = 3.14159265f;

// Estructura para representar un punto 3D
struct Punto3D {
    float x, y, z;
};

// Función para crear la ventana
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void DibujarCubo(HDC hdc, const std::vector<Punto3D>& puntos, const std::vector<std::pair<int, int>>& vertices, float angX, float angY) {
    // Transformación y rotación
    std::vector<Punto3D> PuntosRotados;
    for (const auto& punto : puntos) {
        // Rotación sobre el eje X
        float x = punto.x;
        float y = punto.y * cos(angX) - punto.z * sin(angX);
        float z = punto.y * sin(angX) + punto.z * cos(angX);

        // Rotación sobre el eje Y
        float xFinal = x * cos(angY) + z * sin(angY);
        float yFinal = y;
        float zFinal = -x * sin(angY) + z * cos(angY);

        PuntosRotados.push_back({xFinal, yFinal, zFinal});
    }

    // Dibujo de las líneas que conectan los puntos (las aristas del cubo)
    for (auto& vertice : vertices) {
        const auto& p1 = PuntosRotados[vertice.first];
        const auto& p2 = PuntosRotados[vertice.second];

        // Proyección 2D (simple)
        int x1 = static_cast<int>(p1.x * 100 + 320);
        int y1 = static_cast<int>(-p1.y * 100 + 240);
        int x2 = static_cast<int>(p2.x * 100 + 320);
        int y2 = static_cast<int>(-p2.y * 100 + 240);

        // Dibujar la línea
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
    }
}

int main() {
	FreeConsole();
    // Registro de la clase de ventana
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "3D_Cube";
    RegisterClass(&wc);

    // Crear la ventana
    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "Cubo 3D Giratorio", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, wc.hInstance, NULL);
    if (!hwnd) {
        return 1;
    }

    // Mostrar la ventana
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Vértices del cubo 3D
    std::vector<Punto3D> puntos = {
        { 1.0f,  1.0f,  1.0f}, { 1.0f,  1.0f, -1.0f},
        { 1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f, -1.0f},
        {-1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f,  1.0f}, {-1.0f, -1.0f, -1.0f}
    };

    // Conexiones entre los vértices (aristas del cubo)
    std::vector<std::pair<int, int>> vertices = {
        {0, 1}, {1, 3}, {3, 2}, {2, 0},
        {4, 5}, {5, 7}, {7, 6}, {6, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Variables para la rotación
    float angX = 0.0f, angY = 0.0f;

    // Bucle de mensaje principal
    MSG msg = {0};
    while (true) {
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Obtener el contexto de dispositivo
        HDC hdc = GetDC(hwnd);

        // Limpiar la pantalla (fondo blanco)
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW+1));

        // Dibujar el cubo rotado
        DibujarCubo(hdc, puntos, vertices, angX, angY);

        // Liberar el contexto de dispositivo
        ReleaseDC(hwnd, hdc);

        // Incrementar los ángulos para la rotación
        angX += 0.02f;
        angY += 0.03f;

        // Retraso para que la rotación no sea demasiado rapida
        Sleep(16); // Aproximadamente 60 FPS
    }

    return 0;
}

