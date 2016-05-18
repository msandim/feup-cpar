library(tidyr)
library(dplyr)
library(RColorBrewer)
library(ggplot2)

# Format numbers:
#options(digits)

# Import:
data_general <- tbl_df(read.csv("csv/output.csv"))

# Calculate Speedup:
sequential_times <- data_general %>% filter(alg == 0) %>% `$`(time)
data_general <- data_general %>% mutate(Speedup = sequential_times / time)
rm(sequential_times)

# Calcula efficiency:
data_general <- data_general %>% mutate(Efficiency = Speedup / threads)

# Transform in factors:
data_general$alg <- factor(data_general$alg)
data_general$threads <- factor(data_general$threads)
data_general$proc <- factor(data_general$proc)

# Grafico global
data <- data_general %>% filter(alg == 0 | (alg == 1 & threads == 8) | (alg == 2 & proc == 16))
ggplot(data, aes(x=n, y=time, color=alg)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Tempo de execução (s)")
ggsave("plots/plot_global.pdf", width=9, height=3)

# Gráfico do OpenMP - SpeedUp
data <- data_general %>% filter(alg == 1 & threads != '1' & threads != '0')
ggplot(data, aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Speedup") +
  scale_y_continuous(limits = c(1.1, 1.35))
ggsave("plots/plot_mp.pdf", width=9, height=3)

# Gráfico do MPI - SpeedUp
data <- data_general %>% filter(alg == 2)
ggplot(data, aes(x=n, y=Speedup, color=proc)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75, size=0.2) +
  labs(x="N", y="Speedup")
ggsave("plots/plot_mpi.pdf", width=4*1.5, height=3*1.5)

data <- data_general %>% filter(alg == 1)
ggplot(data, aes(x=n, y=Efficiency, color=proc)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75, size=0.2) +
  labs(x="N", y="Speedup")
ggsave("plots/plot_mpi.pdf", width=4*1.5, height=3*1.5)

# Gráfico do MPI/MP - SpeedUp
ggplot(data_general %>% filter(alg == 3 & proc == 4), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_4.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 8), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_8.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 12), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_12.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 16), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_16.pdf", width=4*1.5, height=3*1.5)