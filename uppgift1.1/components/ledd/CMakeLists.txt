idf_component_register(SRCS "ledd.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver
                    REQUIRES esp_timer)
