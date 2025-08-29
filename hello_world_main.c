#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xBinarySemaphore1 = NULL;
SemaphoreHandle_t xBinarySemaphore2 = NULL;
SemaphoreHandle_t xBinarySemaphore3 = NULL;

void Task1(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore1, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 1] - Pedro Henrique Carlini RM88783\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore2); 
        }
    }
}

void Task2(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 2] - Pedro Henrique Carlini RM88783\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore3);
        }
    }
}

void Task3(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore3, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 3] - Pedro Henrique Carlini RM88783\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore1); 
        }
    }
}

void app_main(void)
{
    xBinarySemaphore1 = xSemaphoreCreateBinary();
    xBinarySemaphore2 = xSemaphoreCreateBinary();
    xBinarySemaphore3 = xSemaphoreCreateBinary();
    
    if (xBinarySemaphore1 == NULL || xBinarySemaphore2 == NULL || xBinarySemaphore3 == NULL) 
    {
        printf("Falha ao criar semáforos binários\n");
        return;
    }

    xTaskCreate(Task1, "Task1", 2048, NULL, 5, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 5, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 5, NULL);

    xSemaphoreGive(xBinarySemaphore1);
}