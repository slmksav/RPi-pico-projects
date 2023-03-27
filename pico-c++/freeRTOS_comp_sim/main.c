#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

// mutex and semaphore handles
static SemaphoreHandle_t xMutex;
static SemaphoreHandle_t xSemaphore;

TaskHandle_t xTaskCpuHandle;
TaskHandle_t xTaskGpuHandle;
TaskHandle_t xTaskRamHandle;
TaskHandle_t xTaskDiskHandle;

// Declare variables for tracking resource usage
uint cpuUsage = 5;
uint gpuUsage = 5;
uint ramUsage = 5;
uint diskUsage = 5;

// simulates CPU usage
void vTaskCpu(void *pvParameters) {
    for (;;) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        cpuUsage++;
        xSemaphoreGive(xSemaphore);

        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("CPU Usage: ");
        for (int i = 0; i < cpuUsage; i++) {
            printf("*");
        }
        printf("\n");
        xSemaphoreGive(xMutex);

        vTaskDelay(100);
    }
}

// simulates GPU usag
void vTaskGpu(void *pvParameters) {
    for (;;) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        gpuUsage++;
        xSemaphoreGive(xSemaphore);

        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("GPU Usage: ");
        for (int i = 0; i < gpuUsage; i++) {
            printf("*");
        }
        printf("\n");
        xSemaphoreGive(xMutex);

        vTaskDelay(150);
    }
}

// simulating ram usage
void vTaskRam(void *pvParameters) {
    for (;;) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        ramUsage++;
        xSemaphoreGive(xSemaphore);

        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("RAM Usage: ");
        for (int i = 0; i < ramUsage; i++) {
            printf("*");
        }
        printf("\n");
        xSemaphoreGive(xMutex);

        vTaskDelay(200);
    }
}

// and disk usage
void vTaskDisk(void *pvParameters) {
    for (;;) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        diskUsage++;
        xSemaphoreGive(xSemaphore);

        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("Disk Usage: ");
        for (int i = 0; i < diskUsage; i++) {
            printf("*");
        }
        printf("\n");
        xSemaphoreGive(xMutex);

        vTaskDelay(250);
    }
}

int main() {
    stdio_init_all();
    vTaskDelay(1000);
    xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL) {
        printf("Failed to create mutex\n");
        return 1;
    }

    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL) {
        printf("Failed to create semaphore\n");
        return 1;
    }

    // init semaphore to unlocked
    xSemaphoreGive(xSemaphore);

    xTaskCreate(vTaskCpu, "CPU Usage", 256, NULL, 1, &xTaskCpuHandle);
    xTaskCreate(vTaskGpu, "GPU Usage", 256, NULL, 1, &xTaskGpuHandle);
    xTaskCreate(vTaskRam, "RAM Usage", 256, NULL, 1, &xTaskRamHandle);
    xTaskCreate(vTaskDisk, "Disk Usage", 256, NULL, 1, &xTaskDiskHandle);

    // start scheduler
    vTaskStartScheduler();

    return 0;
}
